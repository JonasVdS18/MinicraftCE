#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "entity/entity.hpp"
#include <stdint.h>

class Level
{
  public:
    int width, height;
    // array of tile id's
    uint8_t* tiles;
    uint8_t* data;
    int monster_density;
    // array containing all the entities in the level
    Entity** entities;

    Level(int width, int height, int level, Level* parent_level);

  private:
    int depth;
};

#endif
