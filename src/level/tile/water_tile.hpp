#ifndef WATER_TILE_HPP
#define WATER_TILE_HPP
#include "tile.hpp"

class Water_tile : public Tile
{
  public:
    Water_tile(uint8_t _id);
    ~Water_tile();
};

#endif
