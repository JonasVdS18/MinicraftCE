#ifndef SLIME_HPP
#define SLIME_HPP

#include "mob.hpp"

class Slime : public Mob
{
  public:
    Slime(const uint8_t lvl);
    ~Slime();

  private:
    const uint8_t lvl;
    int8_t jump_time;
    int8_t xa, ya;
    void tick() override;
    void render(int x_scroll, int y_scroll) override;

  protected:
    void die() override;
    void touched_by(Entity* entity) override;
};

#endif
