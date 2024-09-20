#include "title_menu.hpp"
#include "gfx/gfx.h"
#include <fontlibc.h>
#include <graphx.h>

// Call the Menu constructor in the initializer list
Title_menu::Title_menu(Game* game, Input_handler* input) : Menu(game, input), selected{0}
{
    options[0] = "Start game";
    options[1] = "How to play";
    options[2] = "About";
}

void Title_menu::tick()
{
    if (input->up->clicked && selected != 0)
    {
        selected--;
    }
    if (input->up->clicked && selected != 2)
    {
        selected++;
    }

    if (input->attack->clicked || input->menu->clicked)
    {
        if (selected == 0)
        {
            game->reset();
            game->set_menu(NULL);
        }
    }
}

void Title_menu::render()
{
    gfx_RLETSprite_NoClip(rlet_logo, (GFX_LCD_WIDTH - rlet_logo_width) / 2, 24);
    fontlib_SetWindow(0, (24 + rlet_logo_width), GFX_LCD_WIDTH, (GFX_LCD_HEIGHT - 24 + rlet_logo_width));
    switch (selected)
    {
    case 0:
        fontlib_DrawString(">Start game<");
        fontlib_DrawString("How to play");
        fontlib_DrawString("About");
        break;

    case 1:
        fontlib_DrawString("Start game");
        fontlib_DrawString(">How to play<");
        fontlib_DrawString("About");
        break;

    case 2:
        fontlib_DrawString("Start game");
        fontlib_DrawString(">How to play<");
        fontlib_DrawString("About");
        break;

    default:
        break;
    }
    fontlib_DrawString("(Arrow keys,2nd and alpha)");
}
