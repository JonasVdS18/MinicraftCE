#ifndef SMASH_PARTICLE_HPP
#define SMASH_PARTICLE_HPP

#include "../entity.hpp"

class Smash_particle : public Entity
{
  public:
    Smash_particle(int x, int y);
    ~Smash_particle();
    void tick() override;
    void render(int x_scroll, int y_scroll) override;

  private:
    uint8_t time;
};

#endif
