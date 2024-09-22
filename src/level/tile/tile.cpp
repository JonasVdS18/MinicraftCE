#include "tile.hpp"
#include "../../entity/entity.hpp"
#include "../../entity/mob.hpp"
#include "../../entity/player.hpp"
#include "../level.hpp"
#include "rock_tile.hpp"
#include <stdint.h>

int Tile::tickCount = 0;
Tile* Tile::tiles[256];
Tile* Tile::rock = new Rock_tile(1);

Tile::Tile(uint8_t _id) : id(_id)
{
    connects_to_grass = false;
    connects_to_lava = false;
    connects_to_sand = false;
    connects_to_water = false;

    tiles[id] = this;
}

void Tile::render(Level* level, int x, int y)
{
}

bool Tile::may_pass(Level* level, int x, int y, Entity* e)
{
    return true;
}

int Tile::get_light_radius(Level* level, int x, int y)
{
    return 0;
}

void Tile::hurt(Level* level, int x, int y, Mob* source, int dmg, int attack_dir)
{
}

void Tile::bumped_into(Level* level, int xt, int yt, Entity* entity)
{
}

void Tile::tick(Level* level, int xt, int yt)
{
}

void Tile::stepped_on(Level* level, int xt, int yt, Entity* entity)
{
}

bool Tile::interact(Level* level, int xt, int yt, Player* player, Item* item, int attack_dir)
{
    return false;
}

bool Tile::connects_to_liquid()
{
    return connects_to_water || connects_to_lava;
}
