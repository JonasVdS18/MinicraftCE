#include "zombie.hpp"
#include "../gfx/gfx.h"
#include "player.hpp"
#include <sys/util.h>

Zombie::Zombie(uint8_t lvl) : Mob(), xa{0}, ya{0}, lvl{lvl}, random_walk_time{0}
{
    x = 0;
    y = 0;
    health = lvl * lvl * 10;
    maxhealth = health;
}

Zombie::~Zombie()
{
}

void Zombie::tick()
{
    Mob::tick();
    if (level->player != NULL && random_walk_time == 0)
    {
        int xd = level->player->x - x;
        int yd = level->player->y - y;
        if (xd * xd + yd * yd < 50 * 50)
        {
            if (xd < 0)
            {
                xa = -1;
            }
            else if (xd > 0)
            {
                xa = +1;
            }
            else
            {
                xa = 0;
            }

            if (yd < 0)
            {
                ya = -1;
            }
            else if (yd > 0)
            {
                ya = +1;
            }
            else
            {
                ya = 0;
            }
        }
        uint8_t speed = tick_time & 1;
        if (!move(xa * speed, ya * speed) || randInt(0, 200) == 0)
        { // moves the zombie, doubles as a check to see if it's still moving -OR- random chance out of 200
            random_walk_time = 60;                    // sets the not-so-random walk time to 60
            xa = (randInt(0, 3) - 1) * randInt(0, 2); // sets the acceleration to random i.e. idling code
            ya = (randInt(0, 3) - 1) * randInt(0, 2); // sets the acceleration to random i.e. idling code
        }

        if (random_walk_time > 0)
        {
            random_walk_time--;
        }
    }
}

void Zombie::render(int x_scroll, int y_scroll)
{
    bool flip = false;
    if ((walk_dist % 32) < 16)
    {
        flip = false;
    }
    else
    {
        flip = true;
    }

    const gfx_rletsprite_t* display_sprite;

    if (dir == 0) // if the direction is 0 (Down)...
    {
        if (!flip)
        {
            display_sprite = rlet_zombie_front;
        }
        else
        {
            display_sprite = rlet_zombie_front_flipped_y;
        }
    }
    if (dir == 1) // if the direction is 1 (Up)...
    {
        if (!flip)
        {
            display_sprite = rlet_zombie_back;
        }
        else
        {
            display_sprite = rlet_zombie_back_flipped_y;
        }
    }
    if (dir == 2) // if the direction is 2 (Left)...
    {
        if (!flip)
        {
            display_sprite = rlet_zombie_side_0_flipped_y;
        }
        else
        {
            display_sprite = rlet_zombie_side_1_flipped_y;
        }
    }
    if (dir == 3) // if the direction is 3 (Right)...
    {
        if (!flip)
        {
            display_sprite = rlet_zombie_side_0;
        }
        else
        {
            display_sprite = rlet_zombie_side_1;
        }
    }
    // gfx_RLETSprite_NoClip(display_sprite, (GFX_LCD_WIDTH - rlet_player_front_width) / 2,
    //(GFX_LCD_HEIGHT - rlet_player_front_height) / 2);
    gfx_RLETSprite_NoClip(display_sprite, x - x_scroll - rlet_zombie_front_width / 2 + GFX_LCD_WIDTH / 2,
                          y - y_scroll - rlet_zombie_front_height / 2 + GFX_LCD_HEIGHT / 2);
}

void Zombie::touched_by(Entity* entity)
{
    if ((dynamic_cast<Player*>(entity) == NULL))
    {
        entity->hurt(this, lvl + 1, dir);
    }
}

void Zombie::die()
{
    Mob::die();
}
