#include "smash_particle.hpp"
#include "../../gfx/minigfx1.h"

Smash_particle::Smash_particle(int x, int y) : Entity(), time{0}
{
    this->x = x;
    this->y = y;
}
Smash_particle::~Smash_particle()
{
}
void Smash_particle::tick()
{
    time++;
    if (time > 10)
    {
        remove();
    }
}
void Smash_particle::render(int x_scroll, int y_scroll)
{
    gfx_RLETSprite(rlet_smash_particle, x - x_scroll, y - y_scroll);
}
