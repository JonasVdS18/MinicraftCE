#ifndef STAIRS_TILE_HPP
#define STAIRS_TILE_HPP
#include "tile.hpp"

class Stairs_tile : public Tile
{
  private:
    bool leads_up;

  public:
    Stairs_tile(int _id, bool _leads_up);
    ~Stairs_tile();
};

#endif
