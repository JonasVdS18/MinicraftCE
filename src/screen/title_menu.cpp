#include "title_menu.hpp"
#include "../game.hpp"
#include "../gfx/minigfx1.h"
#include "../input_handler.hpp"
#include "about_menu.hpp"
#include "font.hpp"
#include "instructions_menu.hpp"
#include "menu.hpp"
#include <fontlibc.h>
#include <graphx.h>

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

        if (selected == 1)
        {
            game->set_menu(new Instructions_menu(this->game, this->input));
        }
        if (selected == 2)
        {
            game->set_menu(new About_menu(this->game, this->input));
        }
    }
}

void Title_menu::render()
{
    // fontlib_ClearWindow();
    fontlib_SetWindow(0, (96 + rlet_logo_height), GFX_LCD_WIDTH, (GFX_LCD_HEIGHT - (96 + rlet_logo_height)));
    fontlib_SetCursorPosition(0, (96 + rlet_logo_height));
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    switch (selected)
    {
    case 0:
        fontlib_SetColors(2, 0);
        Font::print_centered("> START GAME <");
        fontlib_SetColors(3, 0);
        fontlib_Newline();
        Font::print_centered("HOW TO PLAY");
        fontlib_Newline();
        Font::print_centered("ABOUT");
        break;

    case 1:
        fontlib_SetColors(3, 0);
        Font::print_centered("START GAME");
        fontlib_SetColors(2, 0);
        fontlib_Newline();
        Font::print_centered("> HOW TO PLAY <");
        fontlib_SetColors(3, 0);
        fontlib_Newline();
        Font::print_centered("ABOUT");
        break;

    case 2:
        fontlib_SetColors(3, 0);
        Font::print_centered("START GAME");
        fontlib_Newline();
        Font::print_centered("HOW TO PLAY");
        fontlib_Newline();
        fontlib_SetColors(2, 0);
        Font::print_centered("> ABOUT <");
        break;

    default:
        break;
    }
    fontlib_SetColors(3, 0);
    fontlib_SetCursorPosition(0, GFX_LCD_HEIGHT - fontlib_GetCurrentFontHeight());
    fontlib_DrawString("(D-PAD, 2ND, ALPHA)");
    gfx_RLETSprite_NoClip(rlet_logo, (GFX_LCD_WIDTH - rlet_logo_width) / 2, 48);
}
