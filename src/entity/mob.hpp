#ifndef MOB_HPP
#define MOB_HPP

#include "../level/level.hpp"
#include "entity.hpp"

class Level;

class Mob : public Entity
{
  public:
    Mob();
    bool find_start_pos(Level* level);
};

#endif
