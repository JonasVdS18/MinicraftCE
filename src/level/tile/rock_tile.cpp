#include "rock_tile.hpp"
#include "../../gfx/gfx.h"
#include <graphx.h>

Rock_tile::Rock_tile(uint8_t _id) : Tile(_id)
{
}

void Rock_tile::render(Level* level, int x, int y)
{
    gfx_Sprite(tile_placeholder, x - tile_placeholder_width / 2, y - tile_placeholder_height / 2);
}
