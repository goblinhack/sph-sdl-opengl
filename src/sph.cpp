#include "my_main.h"
#include "my_gl.h"
#include "my_tile.h"
#include "my_point.h"

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

namespace Constants
{
    const float WIDTH = 1;
    const float HEIGHT = 1;

    const float SCALE = 900;

    const int   NUMBER_PARTICLES = 70;

    const float REST_DENSITY = 1000;

    const float STIFFNESS = 10000;
    const float VISCOCITY = 12000;

    const float GRAVITY = 12000;

    const float PARTICLE_SPACING = 1.0f / NUMBER_PARTICLES;
    const float PARTICLE_VOLUME = PARTICLE_SPACING * PARTICLE_SPACING;
    const float PARTICLE_MASS = PARTICLE_VOLUME * REST_DENSITY;
    const float KERNEL_RANGE = 2 * PARTICLE_SPACING;
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
    numberCellsX = Constants::WIDTH / Constants::KERNEL_RANGE + 1;
    numberCellsY = Constants::HEIGHT / Constants::KERNEL_RANGE + 1;

    cout << "Grid with " << numberCellsX << " x " << numberCellsY << " cells created." << endl;
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

    for (int i = 0; i < particles.size(); i++)
    {
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

        color = 0;
        normal = fpoint();
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
        void calculatePressure();

        void calculateForceDensity();

        void integrationStep(float dt);

        void collisionHandling();
};

SPHSolver::SPHSolver()
{
    int particlesX = NUMBER_PARTICLES / 2.0f;
    int particlesY = NUMBER_PARTICLES;

    numberParticles = particlesX * particlesY;
    particles = vector<Particle>();

    float width = WIDTH / 4.2f;
    float height = 3.0f * HEIGHT / 4.0f;

    FloatRect particleRect = { (WIDTH - width) / 2,
                               HEIGHT - height,
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

    grid.updateStructure(particles);
}

void SPHSolver::render (Visualization vis)
{
    for (int i = 0; i < numberParticles; i++)
    {
        particles[i].force = fpoint(0.0f, 0.0f);
    }

    static auto tile = tile_find_mand("ball");
    static const fpoint sprite_size(TILE_WIDTH / 2, TILE_HEIGHT / 2);

    blit_fbo_bind(FBO_MAP);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_ONE, GL_ZERO);
    glcolorfast(WHITE);

    blit_init();

    // CircleShape circle(0.5f * PARTICLE_SPACING * SCALE);
    for (int i = 0; i < numberParticles; i++)
    {
        // TODO blit here
        //Color c = Color(2 * particles[i].normalLength, 0, 40, 255);
        // circle.setFillColor(particles[i].renderColor);
        // circle.setPosition(particles[i].position * SCALE);
        // rt.draw(circle);
        fpoint at = particles[i].position;
        at *= SCALE;
        tile_blit(tile, at - sprite_size, at + sprite_size);
    }
    blit_flush();
}

void SPHSolver::repulsionForce(fpoint position)
{
    for (int i = 0; i < numberParticles; i++)
    {
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
    for (int i = 0; i < numberParticles; i++)
    {
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
    calculatePressure();
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
    for (int i = 0; i < numberParticles; i++)
    {
        vector<int> neighbors = neighborhoods[i];
        float densitySum = 0.0f;

        for (int n = 0; n < neighbors.size(); n++)
        {
            int j = neighbors[n];

            fpoint x = particles[i].position - particles[j].position;
            densitySum += particles[j].mass * kernel(x, KERNEL_RANGE);
        }

        particles[i].density = densitySum;
    }
}

void SPHSolver::calculatePressure()
{
    for (int i = 0; i < numberParticles; i++)
    {
        particles[i].pressure = max(STIFFNESS * (particles[i].density - REST_DENSITY), 0.0f);
    }
}

void SPHSolver::calculateForceDensity()
{
    for (int i = 0; i < numberParticles; i++)
    {
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
    for (int i = 0; i < numberParticles; i++)
    {
        particles[i].velocity += dt * particles[i].force / particles[i].density;
        particles[i].position += dt * particles[i].velocity;
    }
}

void SPHSolver::collisionHandling()
{
    for (int i = 0; i < numberParticles; i++)
    {
        if (particles[i].position.x < 0.0f)
        {
            particles[i].position.x = 0.0f;
            particles[i].velocity.x = -0.5f * particles[i].velocity.x;
        }
        else if (particles[i].position.x > WIDTH)
        {
            particles[i].position.x = WIDTH;
            particles[i].velocity.x = -0.5f * particles[i].velocity.x;
        }

        if (particles[i].position.y < 0.0f)
        {
            particles[i].position.y = 0.0f;
            particles[i].velocity.y = -0.5f * particles[i].velocity.y;
        }
        else if (particles[i].position.y > HEIGHT)
        {
            particles[i].position.y = HEIGHT;
            particles[i].velocity.y = -0.5f * particles[i].velocity.y;
        }
    }
}
