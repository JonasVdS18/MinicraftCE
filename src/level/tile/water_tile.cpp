#include "water_tile.hpp"

Water_tile::Water_tile(uint8_t id) : Tile(id)
{
    connects_to_sand = true;
    connects_to_water = true;
}

Water_tile::~Water_tile()
{
}
