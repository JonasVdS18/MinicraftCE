#ifndef ROCK_TILE_HPP
#define ROCK_TILE_HPP
#include "tile.hpp"

class Rock_tile : public Tile
{
  public:
    Rock_tile(uint8_t _id);
    void render(Level* level, int x, int y) override;
};

#endif
