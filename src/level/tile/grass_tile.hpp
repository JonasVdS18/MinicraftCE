#ifndef GRASS_TILE_HPP
#define GRASS_TILE_HPP
#include "tile.hpp"

class Grass_tile : public Tile
{
  public:
    Grass_tile(uint8_t _id);
    void render(Level* level, int x, int y) override;
    void tick(Level* level, int xt, int yt, int modifier) override;
    bool interact(Level* level, int xt, int yt, Player* player, Item* item, int attack_dir) override;
};

#endif
