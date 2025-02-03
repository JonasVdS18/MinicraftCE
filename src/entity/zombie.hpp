#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "mob.hpp"

class Zombie : public Mob
{
  public:
    Zombie(uint8_t lvl);
    ~Zombie();

  private:
    int8_t xa;
    int8_t ya;
    uint8_t lvl; // how tough the zombie is
    uint8_t random_walk_time;
    void tick() override;
    void render(int x_scroll, int y_scroll) override;
    void touched_by(Entity* entity) override;
    void die() override;
};
#endif
