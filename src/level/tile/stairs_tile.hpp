#ifndef STAIRS_TILE_HPP
#define STAIRS_TILE_HPP
#include "tile.hpp"

class Stairs_tile : public Tile
{
  private:
    bool leads_up;

  public:
    Stairs_tile(uint8_t id, bool leads_up);
    ~Stairs_tile();
};

#endif
