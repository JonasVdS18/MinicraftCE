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
};

#endif
