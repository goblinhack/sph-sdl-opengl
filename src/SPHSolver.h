#pragma once

#include <vector>

#include "Particle.h"
#include "Grid.h"

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
