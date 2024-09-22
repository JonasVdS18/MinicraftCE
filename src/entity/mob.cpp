#include "mob.hpp"
#include "../entity/player.hpp"
#include "../level/level.hpp"
#include <sys/util.h>

class Level;

Mob::Mob() : Mob::Entity()
{
    x = y = 8;
    radius_x = 4;
    radius_y = 3;
}

bool Mob::find_start_pos(Level* level)
{
    int x = randInt(0, level->width - 1);
    int y = randInt(0, level->height - 1);
    int xx = x * 16 + 8; // Get actual pixel coordinates from this tile coord
    int yy = y * 16 + 8;

    if (level->player != NULL)
    {
        int xd = level->player->x - xx; // Get the difference between our attempted spawn x, and the player's x
        int yd = level->player->y - yy; // Get the difference between our attempted spawn y, and the player's y
        if (xd * xd + yd * yd < 80 * 80)
            return false; // Use pythagoras' theorem to determine the distance between us and the player, and if it is
                          // less than 80 (too close) then return false
    }

    int r = level->monster_density *
            16; // Get the allowed density of mobs in the level, convert it from a tile to a real coordinate
    if (level->get_entities(xx - r, yy - r, xx + r, yy + r)->size() > 0)
        return false; // Get a list of mobs in the level, within a box centered on our attempted coordinates, with
                      // dimensions of r times 2, and if there are any close to us, return false;

    if (level->get_tile(x, y)->may_pass(level, x, y, this))
    { // Check if the tile we're trying to spawn on is not solid to us
        this->x = xx;
        this->y = yy;
        return true;
    }

    return false;
}
