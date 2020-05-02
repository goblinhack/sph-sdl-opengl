#include "my_game.h"
#include "my_main.h"
#include "my_gl.h"
#include "my_tile.h"
#include "my_point.h"

#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

typedef struct {
public:
    float left;   ///< Left coordinate of the rectangle
    float top;    ///< Top coordinate of the rectangle
    float width;  ///< Width of the rectangle
    float height; ///< Height of the rectangle
} FloatRect;

static float GL_WIDTH;
static float GL_HEIGHT;

static const int GL_BORDER = 100;
static const int GRID_BORDER = 50;
static const float NEB_RADIUS = 8;

namespace Constants
{
    const int   NUMBER_PARTICLES = 50;
    const float BOUNCE        = 1.0;
    const float TIMESTEP      = 0.0001;
    const float REST_DENSITY  = 10000;
    const float STIFFNESS     = 1.44e+09;
    const float VISCOCITY     = 1.44e+09;
    const float REPULSION     = 800000;
    const float GRAVITY       = 3e+07;
    const float PARTICLE_MASS = 2.46914e+07;
    const float KERNEL_RANGE  = TILE_WIDTH;
}
using namespace Constants;

typedef std::vector<int> Cell;

bool Game::is_oob (const fpoint &at)
{
    return (at.x < 0) || (at.y < 0) ||
           (at.x >= config.inner_pix_width) ||
           (at.y >= config.inner_pix_height);
}

bool Game::is_oob (const Particle *p)
{
    return is_oob(p->at);
}

spoint point_to_grid (const fpoint &p)
{
    return spoint(((p.x / GL_WIDTH) * (PARTICLES_WIDTH - (GRID_BORDER * 2))) + GRID_BORDER,
                  ((p.y / GL_HEIGHT) * (PARTICLES_HEIGHT - (GRID_BORDER * 2))) + GRID_BORDER);
}

spoint particle_to_grid (const Particle *p)
{
    return point_to_grid(p->at);
}

Particle* Game::new_particle (const fpoint &at)
{
    static uint32_t next_idx;
    uint32_t tries = PARTICLE_MAX;
    auto p = getptr(particles, next_idx);
    auto eop = getptr(particles, PARTICLE_MAX - 1);
    do {
        p++;
        next_idx++;
        if (unlikely(p > eop)) {
            p = getptr(particles, 0);
            next_idx = 0;
            continue;
        }

        if (p->in_use) {
            continue;
        }

        p->at = at;
        p->density = 0;
        p->force = fpoint(0, 0);
        p->in_use = true;
        p->mass = Constants::PARTICLE_MASS;
        p->pressure = 0;
        p->velocity = fpoint(0, 0);
        num_particles++;

        //auto angle = random_range(0, 360) * (1.0 / RAD_360);
        //float scale = 0.05;
        //sincosf(angle, &p->force.x, &s->force.y);
        //s->velocity.x *= scale;
        //s->velocity.y *= scale;

        attach_particle(p);

        return (p);
    } while (tries--);

    return (nullptr);
}

void Game::free_particle (Particle *p)
{
    auto idx = p - getptr(particles, 0);
    auto s = getptr(particles, idx);
    if (!s->in_use) {
        return;
    }
    s->in_use = false;
    num_particles--;
}

void Game::attach_particle (Particle *p)
{
    auto sp = particle_to_grid(p);
    p->attach_at = sp;
    for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
        auto idp = &getref(all_particle_ids_at, sp.x, sp.y, slot);
        if (!*idp) {
            auto idx = p - getptr(particles, 0);
            *idp = idx;
            return;
        }
    }
    free_particle(p);
    CON("cannot attach to %d,%d out of slots", sp.x, sp.y);
}

void Game::detach_particle (Particle *p)
{
    auto sp = p->attach_at;
    auto idx = p - getptr(particles, 0);
    for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
        auto idp = &getref(all_particle_ids_at, sp.x, sp.y, slot);
        if (*idp == idx) {
            *idp = 0;
            return;
        }
    }
    DIE("cannot detach");
}

void Game::move_particle (Particle *p, fpoint to)
{
    auto new_at = point_to_grid(to);
    if (p->attach_at == new_at) {
        p->at = to;
        return;
    }

    detach_particle(p);
    p->at = to;
    attach_particle(p);
}

#define FOR_ALL_PARTICLES(p) \
    auto pidx = 0; \
    auto p = getptr(game->particles, 0); \
    auto eop = getptr(game->particles, PARTICLE_MAX - 1); \
    for (pidx = 0; p != eop; p++, pidx++) { \
        if (!p->in_use) { \
            continue; \
        } \

#define FOR_ALL_PARTICLES_END() }

#define FOR_ALL_NEBS(p, q) \
    auto sp = particle_to_grid(p); \
    for (int ox = sp.x - NEB_RADIUS; ox <= sp.x + NEB_RADIUS; ox++) { \
        for (int oy = sp.y - NEB_RADIUS; oy <= sp.y + NEB_RADIUS; oy++) { \
            for (int slot = 0; slot < PARTICLE_SLOTS; slot++) { \
                auto qidx = get(game->all_particle_ids_at, ox, oy, slot); \
 \
                auto q = getptr(game->particles, qidx); \
                if (likely(!qidx)) { \
                    continue; \
                } \
 \
                fpoint d = p->at - q->at; \
                float dist = d.x * d.x + d.y * d.y; \
                if (dist > KERNEL_RANGE * KERNEL_RANGE) { \
                    continue; \
                } \

#define FOR_ALL_NEBS_END() } } }

class SPHSolver {
public:
    SPHSolver();
    void update(float dt);
    void render(void);
    void repulsionForce(fpoint at);
    void attractionForce(fpoint at);
private:
    float kernel(fpoint x, float h);
    fpoint gradKernel(fpoint x, float h);
    float laplaceKernel(fpoint x, float h);
    void calculateDensity();
    void calculateForceDensity();
    void integrationStep(float dt);
};

static SPHSolver *sph;

SPHSolver::SPHSolver()
{
    MINICON("Grid with %d x %d", PARTICLES_WIDTH, PARTICLES_HEIGHT);

    for (auto i = 0; i < NUMBER_PARTICLES; i++) {
        int x = random_range(GL_BORDER * 2, GL_WIDTH / 2 - GL_BORDER * 4);
        for (auto j = 0; j < NUMBER_PARTICLES; j++) {
            game->new_particle(fpoint(x++,
                                      random_range(GL_BORDER * 2, GL_BORDER * 3)));
        }
    }

    MINICON("%d particles", game->num_particles);

}

void SPHSolver::render (void)
{
    static auto tile = tile_find_mand("ball");
    static const fpoint sprite_size(TILE_WIDTH / 2, TILE_HEIGHT / 2);

    blit_fbo_bind(FBO_MAP);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_ONE, GL_ZERO);
    glcolorfast(WHITE);

    blit_init();

    FOR_ALL_PARTICLES(p) {
        p->force = fpoint(0.0f, 0.0f);
        fpoint at = p->at;
        tile_blit(tile, at - sprite_size, at + sprite_size);
    } FOR_ALL_PARTICLES_END()

    blit_flush();
}

void SPHSolver::repulsionForce(fpoint at)
{
    for (auto p : game->particles) {
        fpoint x = p.at - at;
        float dist2 = x.x * x.x + x.y * x.y;
        if (dist2 < KERNEL_RANGE * 3) {
            p.force += x * REPULSION * p.density;
        }
    }
}

void SPHSolver::attractionForce (fpoint at)
{
    FOR_ALL_PARTICLES(p) {
        fpoint x = at - p->at;

        float dist2 = x.x * x.x + x.y * x.y;
        if (dist2 < KERNEL_RANGE * 3) {
            p->force += x * REPULSION * p->density;
        }
    } FOR_ALL_PARTICLES_END()
}

void SPHSolver::update(float dt)
{
    calculateDensity();
    calculateForceDensity();
    integrationStep(dt);
}

// Poly6 Kernel
float SPHSolver::kernel(fpoint x, float h)
{
    float r2 = x.x * x.x + x.y * x.y;
    float h2 = h * h;

    if (r2 < 0 || r2 > h2) return 0.0f;

    return 315.0f / (64.0f * M_PI * pow(h, 9)) * pow(h2 - r2, 3);
}

// Gradient of Spiky Kernel
fpoint SPHSolver::gradKernel(fpoint x, float h)
{
    float r = sqrt(x.x * x.x + x.y * x.y);
    if (r == 0.0f) return fpoint(0.0f, 0.0f);

    float t1 = -45.0f / (M_PI * pow(h, 6));
    fpoint t2 = x / r;
    float t3 = pow(h - r, 2);


    return t2 * t1 * t3;
}

// Laplacian of Viscosity Kernel
float SPHSolver::laplaceKernel(fpoint x, float h)
{
    float r = sqrt(x.x * x.x + x.y * x.y);
    return 45.0f / (M_PI * pow(h, 6)) * (h - r);
}

void SPHSolver::calculateDensity()
{
    FOR_ALL_PARTICLES(p) {
        float densitySum = 0.0f;
        FOR_ALL_NEBS(p, q) {
            fpoint x = p->at - q->at;
            densitySum += q->mass * kernel(x, KERNEL_RANGE);
        } FOR_ALL_NEBS_END()

        p->density = densitySum;
        p->pressure = std::max(STIFFNESS * (p->density - REST_DENSITY), 0.0f);
    } FOR_ALL_PARTICLES_END()
}

void SPHSolver::calculateForceDensity()
{
    FOR_ALL_PARTICLES(p) {
        fpoint fPressure = fpoint(0.0f, 0.0f);
        fpoint fViscosity = fpoint(0.0f, 0.0f);
        fpoint fGravity = fpoint(0.0f, 0.0f);
        FOR_ALL_NEBS(p, q) {
            fpoint x = p->at - q->at;

            // Pressure force density
            fPressure += q->mass *
                         (p->pressure + q->pressure) /
                         (2.0f * q->density) *
                         gradKernel(x, KERNEL_RANGE);

            // Viscosity force density
            fViscosity += q->mass *
                          (q->velocity - p->velocity) /
                          q->density * laplaceKernel(x, KERNEL_RANGE);
        } FOR_ALL_NEBS_END()

        // Gravitational force density
        fGravity = p->density * fpoint(0, GRAVITY);

        fPressure *= -1.0f;
        fViscosity *= VISCOCITY;

        //p->force += fPressure + fViscosity + fGravity + fSurface;
        p->force += fPressure + fViscosity + fGravity;
    } FOR_ALL_PARTICLES_END()
}

void SPHSolver::integrationStep(float dt)
{
    FOR_ALL_PARTICLES(p) {
        p->velocity += dt * p->force / p->density;
        fpoint new_at = p->at + dt * p->velocity;
        game->move_particle(p, new_at);

        if (new_at.x < GL_BORDER) {
            new_at.x = GL_BORDER;
            p->velocity.x = -BOUNCE * p->velocity.x;
            game->move_particle(p, new_at);
        } else if (new_at.x > GL_WIDTH - GL_BORDER) {
            new_at.x = GL_WIDTH - GL_BORDER;
            p->velocity.x = -BOUNCE * p->velocity.x;
            game->move_particle(p, new_at);
        }

        if (new_at.y < GL_BORDER) {
            new_at.y = GL_BORDER;
            p->velocity.y = -BOUNCE * p->velocity.y;
            game->move_particle(p, new_at);
        } else if (new_at.y > GL_HEIGHT - GL_BORDER) {
            new_at.y = GL_HEIGHT - GL_BORDER;
            p->velocity.y = -BOUNCE * p->velocity.y;
            game->move_particle(p, new_at);
        }

    } FOR_ALL_PARTICLES_END()
}
#if 0
    for (auto p = particles.begin(); p != particles.end(); p++, i++) {
        particles[i].velocity += dt * particles[i].force / particles[i].density;
        particles[i].at += dt * particles[i].velocity;
    }
}

void SPHSolver::collisionHandling()
{
    int i = 0;
    for (auto p = particles.begin(); p != particles.end(); p++, i++) {
        if (particles[i].at.x < 0.0f) {
            particles[i].at.x = 0.0f;
            particles[i].velocity.x = -1.0f * particles[i].velocity.x;
        } else if (particles[i].at.x > GL_WIDTH) {
            particles[i].at.x = GL_WIDTH;
            particles[i].velocity.x = -1.0f * particles[i].velocity.x;
        }

        if (particles[i].at.y < 0.0f) {
            particles[i].at.y = 0.0f;
            particles[i].velocity.y = -1.0f * particles[i].velocity.y;
        } else if (particles[i].at.y > GL_HEIGHT) {
            particles[i].at.y = GL_HEIGHT;
            particles[i].velocity.y = -1.0f * particles[i].velocity.y;
        }
    }
}
#endif


void sph_display (void)
{
    if (!sph) {
        DIE("no sph");
    }
    sph->update(TIMESTEP);
    sph->render();

    static int tick;
    if (tick++ >= 100) {
        MINICON("%d particles", game->num_particles);
        int x = random_range(GL_BORDER * 2, GL_WIDTH - GL_BORDER * 4);
        while (tick > 0) {
            tick--;
            game->new_particle(fpoint(x + tick,
                                      random_range(GL_BORDER * 2, GL_BORDER * 3)));
        }
        tick = 0;
    }
}

void sph_init (void)
{
    GL_WIDTH = game->config.inner_pix_width;
    GL_HEIGHT = game->config.inner_pix_height;

    if (sph) {
        delete sph;
    }
    sph = new SPHSolver();
}
