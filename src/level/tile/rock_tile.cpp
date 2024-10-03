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
    int screen_x{x * 32 - level->player->x};
    int screen_y{y * 32 - level->player->y};
    gfx_Sprite(tile_placeholder, screen_x - tile_placeholder_width / 2, screen_y - tile_placeholder_height / 2);
}
