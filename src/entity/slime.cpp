#include "slime.hpp"
#include "../gfx/minigfx1.h"
#include "player.hpp"
#include <debug.h>
#include <sys/util.h>

Slime::Slime(const uint8_t lvl) : Mob(), lvl{lvl}, jump_time{0}
{
    x = 0;
    y = 0;
    health = 5 * lvl * lvl;
    maxhealth = health;
}

Slime::~Slime()
{
}

void Slime::tick()
{
    // dbg_printf("SLIME TICK\n");
    Mob::tick();

    uint8_t speed = 1;
    if (!move(xa * speed, ya * speed) || randInt(0, 39) == 0)
    {
        if (jump_time <= -10)
        {
            xa = (randInt(0, 4) - 1);
            ya = (randInt(0, 4) - 1);

            if (level->player != nullptr)
            {
                int xd = level->player->x - x;
                int yd = level->player->y - y;

                if (xd * xd + yd * yd < 100 * 100)
                {
                    if (xd < 0)
                        xa = -2;
                    if (xd > 0)
                        xa = +2;
                    if (yd < 0)
                        ya = -2;
                    if (yd > 0)
                        ya = +2;
                }
            }

            if (xa != 0 || ya != 0)
                jump_time = 10;
        }
    }

    jump_time--;
    if (jump_time == 0)
    {
        xa = 0;
        ya = 0;
    }
}

void Slime::render(int x_scroll, int y_scroll)
{
    const gfx_rletsprite_t* display_sprite;

    // if we are jumping
    if (jump_time > 0)
    {
        display_sprite = rlet_slime_jump;
    }
    else
    {
        display_sprite = rlet_slime;
    }

    if (hurt_time > 0)
    {
        // make color white
    }
    gfx_RLETSprite(display_sprite, x - x_scroll, y - y_scroll);
}

void Slime::die()
{
    Mob::die();

    uint8_t count = 2 * (randInt(0, 1) + 1);
    //!!!!!!!!!!
    /*
    for (uint8_t i = 0; i < count; i++)
    {
        level.add(new ItemEntity(new ResourceItem(Resource.slime), x + random.nextInt(11) - 5,
                                 y + random.nextInt(11) - 5));
    }
    */

    if (level->player != nullptr)
    {
        level->player->score += 25 * lvl;
    }
}

void Slime::touched_by(Entity* entity)
{
    if (level->player != nullptr)
    {
        if (level->player == entity)
        {
            entity->hurt(this, lvl, dir);
        }
    }
}
