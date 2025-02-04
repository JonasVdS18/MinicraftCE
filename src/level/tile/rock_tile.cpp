#include "rock_tile.hpp"
#include "../../entity/player.hpp"
#include "../../gfx/gfx.h"
#include "../level.hpp"
#include <graphx.h>

Rock_tile::Rock_tile(uint8_t id) : Tile(id)
{
}

void Rock_tile::render(Level* level, int x, int y)
{
    int screen_x{(x << 5) - level->x_offset};
    int screen_y{(y << 5) - level->y_offset};
    gfx_Sprite(tile_placeholder, screen_x, screen_y);
}
