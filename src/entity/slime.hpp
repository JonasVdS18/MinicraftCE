#ifndef SLIME_HPP
#define SLIME_HPP

#include "mob.hpp"

class Slime : public Mob
{
  public:
    Slime(int lvl);
    ~Slime();

  private:
    int lvl;
};

#endif
