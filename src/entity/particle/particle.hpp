#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "../entity.hpp"

class Particle : public Entity
{
  public:
    Particle();
    ~Particle();
    virtual void tick() override;
};

#endif
