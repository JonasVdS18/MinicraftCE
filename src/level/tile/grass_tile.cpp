#include "grass_tile.hpp"
#include "../../gfx/gfx.h"
#include "../level.hpp"
#include <graphx.h>

Grass_tile::Grass_tile(uint8_t _id) : Tile(_id)
{
    connects_to_grass = true;
}

void Grass_tile::render(Level* level, int x, int y)
{
    bool connected_up = level->get_tile(x, y - 1)->connects_to_grass;
    bool connected_down = level->get_tile(x, y + 1)->connects_to_grass;
    bool connected_left = level->get_tile(x - 1, y)->connects_to_grass;
    bool connected_right = level->get_tile(x + 1, y)->connects_to_grass;

    if (connected_up && connected_left)
    {
        gfx_Sprite(grass_tile_ul, x - grass_tile_ul_width / 2, y - grass_tile_dl_height / 2);
    }
    else
    {
        gfx_Sprite(grass_tile_endpiece_0, x - grass_tile_endpiece_0_width / 2, y - grass_tile_endpiece_0_height / 2);
    }

    if (connected_up && connected_right)
    {
        gfx_Sprite(grass_tile_ur, x - grass_tile_ur_width / 2, y - grass_tile_ur_height / 2);
    }
    else
    {
        gfx_Sprite(grass_tile_endpiece_0_flipped_y, x - grass_tile_endpiece_0_flipped_y_width / 2,
                   y - grass_tile_endpiece_0_flipped_y_height / 2);
    }

    if (connected_down && connected_left)
    {
        gfx_Sprite(grass_tile_dl, x - grass_tile_dl_width / 2, y - grass_tile_dl_height / 2);
    }
    else
    {
        gfx_Sprite(grass_tile_endpiece_0_flipped_x, x - grass_tile_endpiece_0_flipped_x_width / 2,
                   y - grass_tile_endpiece_0_flipped_x_height / 2);
    }

    if (connected_down && connected_right)
    {
        gfx_Sprite(grass_tile_dr, x - grass_tile_dr_width / 2, y - grass_tile_dr_height / 2);
    }
    else
    {
        gfx_Sprite(grass_tile_endpiece_0_flipped_xy, x - grass_tile_endpiece_0_flipped_xy_width / 2,
                   y - grass_tile_endpiece_0_flipped_xy_height / 2);
    }
}

void Grass_tile::tick(Level* level, int xt, int yt)
{
}

bool Grass_tile::interact(Level* level, int xt, int yt, Player* player, Item* item, int attack_dir)
{
}
