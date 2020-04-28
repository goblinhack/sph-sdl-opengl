#pragma once

#include "my_point.h"

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
