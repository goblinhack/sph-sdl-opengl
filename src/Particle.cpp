#include "Particle.h"

#include "Constants.h"

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
