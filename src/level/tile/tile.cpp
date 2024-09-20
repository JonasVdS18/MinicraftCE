#include "tile.hpp"

int Tile::tickCount = 0;

Tile::Tile(uint8_t _id) : id(_id)
{
    tiles[id] = this;
    connects_to_grass = false;
    connects_to_lava = false;
    connects_to_sand = false;
    connects_to_water = false;
}

bool Tile::may_pass(Level* level, int x, int y, Entity* e)
{
    return true;
}

int Tile::get_light_radius(Level* level, int x, int y)
{
    return 0;
}

bool Tile::interact(Level* level, int xt, int yt, Player* player, Item* item, int attack_dir)
{
    return false;
}

bool Tile::connects_to_liquid()
{
    return connects_to_water || connects_to_lava;
}
