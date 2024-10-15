#include "grass_tile.hpp"
#include "../../entity/player.hpp"
#include "../../gfx/gfx.h"
#include "../level.hpp"
#include <graphx.h>

Grass_tile::Grass_tile(uint8_t _id) : Tile(_id)
{
    Tile::connects_to_grass = true;
}

void Grass_tile::render(Level* level, int x, int y)
{
    int screen_x{x * 32 - level->player->x};
    int screen_y{y * 32 - level->player->y};
    bool connected_up = level->get_tile(x, y - 1)->connects_to_grass;
    bool connected_down = level->get_tile(x, y + 1)->connects_to_grass;
    bool connected_left = level->get_tile(x - 1, y)->connects_to_grass;
    bool connected_right = level->get_tile(x + 1, y)->connects_to_grass;

    if (connected_up)
    {
        if (connected_left)
        {
            gfx_Sprite(grass_tile_ul, screen_x - grass_tile_ul_width, screen_y - grass_tile_dl_height);
        }
        else
        {
            gfx_Sprite(grass_tile_endpiece_1_rotated_270, screen_x - grass_tile_endpiece_1_rotated_270_width,
                       screen_y - grass_tile_endpiece_1_rotated_270_height);
        }

        if (connected_right)
        {
            gfx_Sprite(grass_tile_ur, screen_x, screen_y - grass_tile_ur_height);
        }
        else
        {
            gfx_Sprite(grass_tile_endpiece_1_rotated_90, screen_x, screen_y - grass_tile_endpiece_1_rotated_90_height);
        }
    }
    else
    {
        if (connected_left)
        {
            gfx_Sprite(grass_tile_endpiece_1, screen_x - grass_tile_endpiece_1_width,
                       screen_y - grass_tile_endpiece_1_height);
        }
        else
        {
            gfx_Sprite(grass_tile_endpiece_0, screen_x - grass_tile_endpiece_0_width,
                       screen_y - grass_tile_endpiece_0_height);
        }
        if (connected_right)
        {
            gfx_Sprite(grass_tile_endpiece_1, screen_x, screen_y - grass_tile_endpiece_1_height);
        }
        else
        {
            gfx_Sprite(grass_tile_endpiece_0_flipped_y, screen_x, screen_y - grass_tile_endpiece_0_flipped_y_height);
        }
    }

    if (connected_down)
    {
        if (connected_left)
        {
            gfx_Sprite(grass_tile_dl, screen_x - grass_tile_dl_width, screen_y);
        }
        else
        {
            gfx_Sprite(grass_tile_endpiece_1_rotated_270, screen_x - grass_tile_endpiece_1_rotated_270_width, screen_y);
        }
        if (connected_right)
        {
            gfx_Sprite(grass_tile_dr, screen_x, screen_y);
        }
        else
        {
            gfx_Sprite(grass_tile_endpiece_1_rotated_90, screen_x, screen_y);
        }
    }
    else
    {
        if (connected_left)
        {
            gfx_Sprite(grass_tile_endpiece_1_flipped_x, screen_x - grass_tile_endpiece_1_flipped_x_width, screen_y);
        }
        else
        {
            gfx_Sprite(grass_tile_endpiece_0_flipped_x, screen_x - grass_tile_endpiece_0_flipped_x_width, screen_y);
        }
        if (connected_right)
        {
            gfx_Sprite(grass_tile_endpiece_1_flipped_x, screen_x, screen_y);
        }
        else
        {
            gfx_Sprite(grass_tile_endpiece_0_flipped_xy, screen_x, screen_y);
        }
    }
}

void Grass_tile::tick(Level* level, int xt, int yt, int modifier)
{
}

bool Grass_tile::interact(Level* level, int xt, int yt, Player* player, Item* item, int attack_dir)
{
}
