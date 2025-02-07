#ifndef GRASS_TILE_HPP
#define GRASS_TILE_HPP
#include "tile.hpp"

class Grass_tile : public Tile
{
  public:
    Grass_tile(uint8_t _id);
    void tick(Level* level, int xt, int yt, uint8_t modifier) override;
    bool interact(Level* level, int xt, int yt, Player* player, Item* item, uint8_t attack_dir) override;
};

#endif
