#ifndef SLIME_HPP
#define SLIME_HPP

#include "mob.hpp"

class Slime : public Mob
{
  public:
    Slime(int lvl);

  private:
    int lvl;
};

#endif
