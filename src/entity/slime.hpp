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
    void tick() override;
    void render(int x_scroll, int y_scroll) override;
};

#endif
