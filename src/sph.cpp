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
    double left;   ///< Left coordinate of the rectangle
    double top;    ///< Top coordinate of the rectangle
    double width;  ///< Width of the rectangle
    double height; ///< Height of the rectangle
} FloatRect;

class Particle
{
public:
    fpoint position;
    fpoint velocity;
    fpoint force;

    double mass;
    double density;
    double pressure;

    double color;
    fpoint normal;

    Particle();
    Particle(fpoint position);

    double getVelocityLength2() const;
    double getForceLength2() const;
    double getNormalLength2() const;
};

namespace Constants
{
    const double GL_WIDTH = 1340;
    const double GL_HEIGHT = 800;

    const double SCALE = 1;

    const int   NUMBER_PARTICLES = 90;

    const double REST_DENSITY = 10000; // higher more "frothy"

    const double STIFFNESS = 18000 * 80000; // higher more gas like
    const double VISCOCITY = 18000 * 80000;

    const double GRAVITY = 150 * 200000;

    const double PARTICLE_SPACING = 1000.0f / NUMBER_PARTICLES;
    const double PARTICLE_VOLUME = 20 * PARTICLE_SPACING * PARTICLE_SPACING;
    const double PARTICLE_MASS = PARTICLE_VOLUME * REST_DENSITY;
    const double KERNEL_RANGE = 2 * PARTICLE_SPACING;
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
    numberCellsX = Constants::GL_WIDTH / Constants::KERNEL_RANGE + 1;
    numberCellsY = Constants::GL_HEIGHT / Constants::KERNEL_RANGE + 1;
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

double Particle::getVelocityLength2() const
{
        return velocity.x * velocity.x + velocity.y * velocity.y;
}

double Particle::getForceLength2() const
{
        return force.x * force.x + force.y * force.y;
}

double Particle::getNormalLength2() const
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

        void update(double dt, Visualization vis);
        void render(Visualization vis);

        void repulsionForce(fpoint position);
        void attractionForce(fpoint position);

private:
        int numberParticles;
        std::vector<Particle> particles;
        std::vector<std::vector<int>> neighborhoods;
        Grid grid;

        double kernel(fpoint x, double h);
        fpoint gradKernel(fpoint x, double h);
        double laplaceKernel(fpoint x, double h);

        void findNeighborhoods();

        void calculateDensity();
        void calculatePressure();

        void calculateForceDensity();

        void integrationStep(double dt);

        void collisionHandling();
};

static SPHSolver *sph;

SPHSolver::SPHSolver()
{
    int particlesX = NUMBER_PARTICLES / 2.0f;
    int particlesY = NUMBER_PARTICLES;

    numberParticles = particlesX * particlesY;
    particles = vector<Particle>();

    double width = GL_WIDTH / 4.2f;
    double height = 3.0f * GL_HEIGHT / 4.0f;

    FloatRect particleRect = { (GL_WIDTH - width) / 2,
                               GL_HEIGHT - height,
                               width, height
                             };

    double dx = particleRect.width / particlesX;
    double dy = particleRect.height / particlesY;

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

        double dist2 = x.x * x.x + x.y * x.y;

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

        double dist2 = x.x * x.x + x.y * x.y;

        if (dist2 < KERNEL_RANGE * 3)
        {
            particles[i].force += x * 800000.0f * particles[i].density;
        }
    }
}

void SPHSolver::update(double dt, Visualization vis)
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
double SPHSolver::kernel(fpoint x, double h)
{
    double r2 = x.x * x.x + x.y * x.y;
    double h2 = h * h;

    if (r2 < 0 || r2 > h2) return 0.0f;

    return 315.0f / (64.0f * M_PI * pow(h, 9)) * pow(h2 - r2, 3);
}

// Gradient of Spiky Kernel
fpoint SPHSolver::gradKernel(fpoint x, double h)
{
    double r = sqrt(x.x * x.x + x.y * x.y);
    if (r == 0.0f) return fpoint(0.0f, 0.0f);

    double t1 = -45.0f / (M_PI * pow(h, 6));
    fpoint t2 = x / r;
    double t3 = pow(h - r, 2);


    return t2 * t1 * t3;
}

// Laplacian of Viscosity Kernel
double SPHSolver::laplaceKernel(fpoint x, double h)
{
    double r = sqrt(x.x * x.x + x.y * x.y);
    return 45.0f / (M_PI * pow(h, 6)) * (h - r);
}

void SPHSolver::findNeighborhoods()
{
    neighborhoods = vector<vector<int>>();
    double maxDist2 = KERNEL_RANGE * KERNEL_RANGE;

    for (const Particle &p : particles)
    {
        vector<int> neighbors = vector<int>();
        vector<Cell> neighboringCells = grid.getNeighboringCells(p.position);

        for (const Cell &cell : neighboringCells)
        {
            for (int index : cell)
            {
                fpoint x = p.position - particles[index].position;
                double dist2 = x.x * x.x + x.y * x.y;
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
        double densitySum = 0.0f;

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
        particles[i].pressure =
            std::max(STIFFNESS * (particles[i].density - REST_DENSITY), 0.0);
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

void SPHSolver::integrationStep(double dt)
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
        else if (particles[i].position.x > GL_WIDTH)
        {
            particles[i].position.x = GL_WIDTH;
            particles[i].velocity.x = -0.5f * particles[i].velocity.x;
        }

        if (particles[i].position.y < 0.0f)
        {
            particles[i].position.y = 0.0f;
            particles[i].velocity.y = -0.5f * particles[i].velocity.y;
        }
        else if (particles[i].position.y > GL_HEIGHT)
        {
            particles[i].position.y = GL_HEIGHT;
            particles[i].velocity.y = -0.5f * particles[i].velocity.y;
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
    if (sph) {
        delete sph;
    }
    sph = new SPHSolver();
}
