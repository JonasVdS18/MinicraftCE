#ifndef SLIME_HPP
#define SLIME_HPP

#include "mob.hpp"

class Slime : public Mob
{
  public:
    Slime(const unsigned int lvl);
    ~Slime();

  private:
    const unsigned int lvl;
    int jump_time;
    int xa, ya;
    void tick() override;
    void render(int x_scroll, int y_scroll) override;

  protected:
    void die();
    void touched_by(Entity* entity) override;
};

#endif
