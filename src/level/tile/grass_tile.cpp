#include "grass_tile.hpp"
#include "../../entity/player.hpp"
#include "../../gfx/minigfx1.h"
#include "../level.hpp"
#include <graphx.h>

Grass_tile::Grass_tile(uint8_t _id) : Tile(_id)
{
    Tile::connects_to_grass = true;
}
void Grass_tile::tick(Level* level, int xt, int yt, int modifier)
{
}

bool Grass_tile::interact(Level* level, int xt, int yt, Player* player, Item* item, int attack_dir)
{
}
