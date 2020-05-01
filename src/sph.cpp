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

class Particle
{
public:
    fpoint position;
    fpoint velocity;
    fpoint force;

    float mass;
    float density;
    float pressure;

    float color;
    fpoint normal;

    Particle();
    Particle(fpoint position);

    float getVelocityLength2() const;
    float getForceLength2() const;
    float getNormalLength2() const;
};

static float GL_WIDTH;
static float GL_HEIGHT;

namespace Constants
{
    const float SCALE = 1;

    const int   NUMBER_PARTICLES = 90;

    const float REST_DENSITY = 10000; // higher more "frothy"

    const float STIFFNESS = 18000 * 80000; // higher more gas like
    const float VISCOCITY = 18000 * 80000;

    const float GRAVITY = 150 * 200000;

    const float PARTICLE_SPACING = 1000.0f / NUMBER_PARTICLES;
    const float PARTICLE_VOLUME = 20 * PARTICLE_SPACING * PARTICLE_SPACING;
    const float PARTICLE_MASS = PARTICLE_VOLUME * REST_DENSITY;
    const float KERNEL_RANGE = TILE_WIDTH;
}
using namespace Constants;

typedef std::vector<int> Cell;

class Grid
{
public:
    Grid();

    void updateStructure(std::vector<Particle> &particles);

    std::vector<Cell> getNeighboringCells(fpoint position);

    int numberCellsX;
    int numberCellsY;

    std::vector<std::vector<Cell>> cells;
};

Grid::Grid()
{
    numberCellsX = GL_WIDTH / Constants::KERNEL_RANGE + 1;
    numberCellsY = GL_HEIGHT / Constants::KERNEL_RANGE + 1;
}

vector<Cell> Grid::getNeighboringCells(fpoint position)
{
    vector<Cell> resultCells = vector<Cell>();

    int xCell = position.x / Constants::KERNEL_RANGE;
    int yCell = position.y / Constants::KERNEL_RANGE;

    resultCells.push_back(cells[xCell][yCell]);
    if (xCell > 0) resultCells.push_back(cells[xCell - 1][yCell]);
    if (xCell < numberCellsX - 1) resultCells.push_back(cells[xCell + 1][yCell]);

    if (yCell > 0) resultCells.push_back(cells[xCell][yCell - 1]);
    if (yCell < numberCellsY - 1) resultCells.push_back(cells[xCell][yCell + 1]);

    if (xCell > 0 && yCell > 0) resultCells.push_back(cells[xCell - 1][yCell - 1]);
    if (xCell > 0 && yCell < numberCellsY - 1) resultCells.push_back(cells[xCell - 1][yCell + 1]);
    if (xCell < numberCellsX - 1 && yCell > 0) resultCells.push_back(cells[xCell + 1][yCell - 1]);
    if (xCell < numberCellsX - 1 && yCell < numberCellsY - 1) resultCells.push_back(cells[xCell + 1][yCell + 1]);

    return resultCells;
}

void Grid::updateStructure(std::vector<Particle> &particles)
{
    cells = vector<vector<Cell>>(numberCellsX,
                                 vector<Cell>(numberCellsY, Cell()));

    int i = 0;
    for (auto p = particles.begin(); p != particles.end(); p++, i++) {
        int xCell = particles[i].position.x / Constants::KERNEL_RANGE;
        int yCell = particles[i].position.y / Constants::KERNEL_RANGE;

        auto v = getptr(cells, xCell, yCell);
        v->push_back(i);
    }
}

Particle::Particle()
{
        Particle(fpoint());
}

Particle::Particle(fpoint pos)
{
        position = pos;
        velocity = fpoint();
        force = fpoint();

        mass = Constants::PARTICLE_MASS;

        density = 0;
        pressure = 0;
}

float Particle::getVelocityLength2() const
{
        return velocity.x * velocity.x + velocity.y * velocity.y;
}

float Particle::getForceLength2() const
{
        return force.x * force.x + force.y * force.y;
}

float Particle::getNormalLength2() const
{
        return normal.x * normal.x + normal.y * normal.y;
}
enum class Visualization
{
        Default,
        Velocity,
        Force,
        Density,
        Pressure,
        Water
};

class SPHSolver
{
public:
        SPHSolver();

        void update(float dt, Visualization vis);
        void render(Visualization vis);

        void repulsionForce(fpoint position);
        void attractionForce(fpoint position);

private:
        int numberParticles;
        std::vector<Particle> particles;
        std::vector<std::vector<int>> neighborhoods;
        Grid grid;

        float kernel(fpoint x, float h);
        fpoint gradKernel(fpoint x, float h);
        float laplaceKernel(fpoint x, float h);

        void findNeighborhoods();

        void calculateDensity();

        void calculateForceDensity();

        void integrationStep(float dt);

        void collisionHandling();
};

static SPHSolver *sph;

SPHSolver::SPHSolver()
{
    int particlesX = NUMBER_PARTICLES / 2.0f;
    int particlesY = NUMBER_PARTICLES;

    numberParticles = particlesX * particlesY;
    particles = vector<Particle>();

    float width = GL_WIDTH / 4.2f;
    float height = 3.0f * GL_HEIGHT / 4.0f;

    FloatRect particleRect = { (GL_WIDTH - width) / 2,
                               GL_HEIGHT - height,
                               width, height
                             };

    float dx = particleRect.width / particlesX;
    float dy = particleRect.height / particlesY;

    for (int i = 0; i < NUMBER_PARTICLES / 2.0f; i++)
    {
        for (int j = 0; j < NUMBER_PARTICLES; j++)
        {
            fpoint pos = fpoint(particleRect.left, particleRect.top) +
                                fpoint(i * dx, j * dy);
            Particle p = Particle(pos);
            particles.push_back(p);
        }
    }

    MINICON("Grid with %d x %d, %zd particles",
            grid.numberCellsX, grid.numberCellsY, particles.size());

    grid.updateStructure(particles);
}

void SPHSolver::render (Visualization vis)
{

    static auto tile = tile_find_mand("ball");
    static const fpoint sprite_size(TILE_WIDTH / 2, TILE_HEIGHT / 2);

    blit_fbo_bind(FBO_MAP);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_ONE, GL_ZERO);
    glcolorfast(WHITE);

    blit_init();

    int i = 0;
    for (auto p = particles.begin(); p != particles.end(); p++, i++) {
        particles[i].force = fpoint(0.0f, 0.0f);
        fpoint at = particles[i].position;
        at *= SCALE;
        tile_blit(tile, at - sprite_size, at + sprite_size);
    }
    blit_flush();
}

void SPHSolver::repulsionForce(fpoint position)
{
    int i = 0;
    for (auto p = particles.begin(); p != particles.end(); p++, i++) {
        fpoint x = particles[i].position - position;

        float dist2 = x.x * x.x + x.y * x.y;

        if (dist2 < KERNEL_RANGE * 3)
        {
            particles[i].force += x * 800000.0f * particles[i].density;
        }
    }
}

void SPHSolver::attractionForce(fpoint position)
{
    int i = 0;
    for (auto p = particles.begin(); p != particles.end(); p++, i++) {
        fpoint x = position - particles[i].position;

        float dist2 = x.x * x.x + x.y * x.y;

        if (dist2 < KERNEL_RANGE * 3)
        {
            particles[i].force += x * 800000.0f * particles[i].density;
        }
    }
}

void SPHSolver::update(float dt, Visualization vis)
{
    findNeighborhoods();
    calculateDensity();
    calculateForceDensity();
    integrationStep(dt);
    collisionHandling();

    grid.updateStructure(particles);
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

void SPHSolver::findNeighborhoods()
{
    neighborhoods = vector<vector<int>>();
    float maxDist2 = KERNEL_RANGE * KERNEL_RANGE;

    for (const Particle &p : particles)
    {
        vector<int> neighbors = vector<int>();
        vector<Cell> neighboringCells = grid.getNeighboringCells(p.position);

        for (const Cell &cell : neighboringCells)
        {
            for (int index : cell)
            {
                fpoint x = p.position - particles[index].position;
                float dist2 = x.x * x.x + x.y * x.y;
                if (dist2 <= maxDist2) {
                    neighbors.push_back(index);
                }
            }
        }

        neighborhoods.push_back(neighbors);
    }
}

void SPHSolver::calculateDensity()
{
    int i = 0;
    for (auto p = particles.begin(); p != particles.end(); p++, i++) {
        vector<int> neighbors = neighborhoods[i];
        float densitySum = 0.0f;

        for (int n = 0; n < neighbors.size(); n++) {
            int j = neighbors[n];

            fpoint x = particles[i].position - particles[j].position;
            densitySum += particles[j].mass * kernel(x, KERNEL_RANGE);
        }

        particles[i].density = densitySum;
        particles[i].pressure =
            std::max(STIFFNESS * (particles[i].density - REST_DENSITY), 0.0f);
    }
}

void SPHSolver::calculateForceDensity()
{
    int i = 0;
    for (auto p = particles.begin(); p != particles.end(); p++, i++) {
        fpoint fPressure = fpoint(0.0f, 0.0f);
        fpoint fViscosity = fpoint(0.0f, 0.0f);
        fpoint fGravity = fpoint(0.0f, 0.0f);

        vector<int> neighbors = neighborhoods[i];

        //particles[i].color = 0;

        for (int n = 0; n < neighbors.size(); n++)
        {
            int j = neighbors[n];
            fpoint x = particles[i].position - particles[j].position;

            // Pressure force density
            fPressure += particles[j].mass *
                         (particles[i].pressure + particles[j].pressure) /
                         (2.0f * particles[j].density) *
                         gradKernel(x, KERNEL_RANGE);

            // Viscosity force density
            fViscosity += particles[j].mass * (particles[j].velocity - particles[i].velocity) / particles[j].density * laplaceKernel(x, KERNEL_RANGE);

            // Color field
            //particles[i].color += particles[j].mass / particles[j].density * kernel(x, KERNEL_RANGE);
        }

        // Gravitational force density
        fGravity = particles[i].density * fpoint(0, GRAVITY);

        fPressure *= -1.0f;
        fViscosity *= VISCOCITY;

        //particles[i].force += fPressure + fViscosity + fGravity + fSurface;
        particles[i].force += fPressure + fViscosity + fGravity;
    }
}

void SPHSolver::integrationStep(float dt)
{
    int i = 0;
    for (auto p = particles.begin(); p != particles.end(); p++, i++) {
        particles[i].velocity += dt * particles[i].force / particles[i].density;
        particles[i].position += dt * particles[i].velocity;
    }
}

void SPHSolver::collisionHandling()
{
    int i = 0;
    for (auto p = particles.begin(); p != particles.end(); p++, i++) {
        if (particles[i].position.x < 0.0f) {
            particles[i].position.x = 0.0f;
            particles[i].velocity.x = -1.0f * particles[i].velocity.x;
        } else if (particles[i].position.x > GL_WIDTH) {
            particles[i].position.x = GL_WIDTH;
            particles[i].velocity.x = -1.0f * particles[i].velocity.x;
        }

        if (particles[i].position.y < 0.0f) {
            particles[i].position.y = 0.0f;
            particles[i].velocity.y = -1.0f * particles[i].velocity.y;
        } else if (particles[i].position.y > GL_HEIGHT) {
            particles[i].position.y = GL_HEIGHT;
            particles[i].velocity.y = -1.0f * particles[i].velocity.y;
        }
    }
}

void sph_display (void)
{
    if (!sph) {
        DIE("no sph");
    }
    sph->update(0.0001, Visualization::Water);
    sph->render(Visualization::Water);
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
