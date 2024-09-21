#include "title_menu.hpp"
#include "../game.hpp"
#include "../gfx/gfx.h"
#include "../input_handler.hpp"
#include "menu.hpp"
#include <fontlibc.h>
#include <graphx.h>

void print_centered(const char* string)
{
    fontlib_SetCursorPosition(fontlib_GetWindowWidth() / 2 + fontlib_GetWindowXMin() -
                                  (fontlib_GetStringWidth(string) / 2),
                              fontlib_GetCursorY());
    fontlib_DrawString(string);
}

// Call the Menu constructor in the initializer list
Title_menu::Title_menu(Game* game, Input_handler* input) : Menu(game, input), selected{0}
{
}

Title_menu::~Title_menu()
{
}

void Title_menu::tick()
{
    if (input->up->clicked && selected > 0)
    {
        selected--;
    }
    if (input->down->clicked && selected < 2)
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
    fontlib_ClearWindow();
    fontlib_SetWindow(0, (96 + rlet_logo_height), GFX_LCD_WIDTH, (GFX_LCD_HEIGHT - (96 + rlet_logo_height)));
    fontlib_SetCursorPosition(0, (96 + rlet_logo_height));
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    switch (selected)
    {
    case 0:
        fontlib_SetColors(2, 0);
        print_centered("> START GAME <");
        fontlib_SetColors(3, 0);
        fontlib_Newline();
        print_centered("HOW TO PLAY");
        fontlib_Newline();
        print_centered("ABOUT");
        break;

    case 1:
        fontlib_SetColors(3, 0);
        print_centered("START GAME");
        fontlib_SetColors(2, 0);
        fontlib_Newline();
        print_centered("> HOW TO PLAY <");
        fontlib_SetColors(3, 0);
        fontlib_Newline();
        print_centered("ABOUT");
        break;

    case 2:
        fontlib_SetColors(3, 0);
        print_centered("START GAME");
        fontlib_Newline();
        print_centered("HOW TO PLAY");
        fontlib_Newline();
        fontlib_SetColors(2, 0);
        print_centered("> ABOUT <");
        break;

    default:
        break;
    }
    gfx_RLETSprite_NoClip(rlet_logo, (GFX_LCD_WIDTH - rlet_logo_width) / 2, 48);
}
