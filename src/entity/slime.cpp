#include "slime.hpp"
#include "../gfx/minigfx1.h"
#include <debug.h>
#include <sys/util.h>

Slime::Slime(const unsigned int lvl) : Mob(), lvl{lvl}, jump_time{0}
{
    x = randInt(0, 64 * 16 - 1);
    y = randInt(0, 64 * 16 - 1);
}

Slime::~Slime()
{
}

void Slime::tick()
{
    // dbg_printf("SLIME TICK\n");
    Mob::tick();
}

void Slime::render(int x_scroll, int y_scroll)
{
    const gfx_rletsprite_t* display_sprite;
    /* our texture in the png file */
    int xt = 0;  // X tile coordinate in the sprite-sheet
    int yt = 18; // Y tile coordinate in the sprite-sheet

    /* where to draw the sprite relative to our position */
    int xo = x - 8;  // the horizontal location to start drawing the sprite
    int yo = y - 11; // the vertical location to start drawing the sprite

    // if we are jumping
    if (jump_time > 0)
    {
        display_sprite = rlet_slime_jump;
    }
    else
    {
        display_sprite = rlet_slime_jump;
    }

    if (hurt_time > 0)
    {
        // make color white
    }
    gfx_RLETSprite(display_sprite, x - x_scroll - rlet_slime_width / 2 + GFX_LCD_WIDTH / 2,
                   y - y_scroll - rlet_slime_height / 2 + GFX_LCD_HEIGHT / 2);
}
