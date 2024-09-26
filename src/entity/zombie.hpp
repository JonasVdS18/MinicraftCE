#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "mob.hpp"

class Zombie : public Mob
{
  public:
    Zombie(const unsigned int lvl);
    ~Zombie();

  private:
    const unsigned int lvl;
};
#endif
