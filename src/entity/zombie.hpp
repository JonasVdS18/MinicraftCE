#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "mob.hpp"

class Zombie : public Mob
{
  public:
    Zombie(int lvl);

  private:
    int lvl;
};
#endif
