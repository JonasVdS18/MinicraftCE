#include "lava_tile.hpp"

Lava_tile::Lava_tile(uint8_t _id) : Tile(id)
{
    connects_to_sand = true;
    connects_to_lava = true;
}

Lava_tile::~Lava_tile()
{
}
