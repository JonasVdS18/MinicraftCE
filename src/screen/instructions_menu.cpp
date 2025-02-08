#include "instructions_menu.hpp"
#include "title_menu.hpp"
#include <fontlibc.h>

// Call the Menu constructor in the initializer list
Instructions_menu::Instructions_menu(Game* game, Input_handler* input) : Menu(game, input)
{
}

Instructions_menu::~Instructions_menu()
{
}

void Instructions_menu::tick()
{
    if (input->attack->clicked || input->menu->clicked)
    {
        game->set_menu(new Title_menu(this->game, this->input));
    }
}

void Instructions_menu::render()
{
    gfx_ZeroScreen();
    // fontlib_ClearWindow();
    fontlib_SetWindowFullScreen();
    fontlib_HomeUp();
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    fontlib_SetColors(2, 0);
    fontlib_DrawString("HOW TO PLAY");
    fontlib_Newline();
    fontlib_Newline();
    fontlib_SetColors(4, 0);
    fontlib_DrawString("MOVE YOUR CHARACTER");
    fontlib_Newline();
    fontlib_DrawString("WITH THE ARROW KEYS");
    fontlib_Newline();
    fontlib_DrawString("PRESS 2ND TO ATTACK");
    fontlib_Newline();
    fontlib_DrawString("AND ALPHA TO OPEN");
    fontlib_Newline();
    fontlib_DrawString("THE INVENTORY AND TO");
    fontlib_Newline();
    fontlib_DrawString("USE ITEMS.");
    fontlib_Newline();
    fontlib_DrawString("SELECT AN ITEM IN");
    fontlib_Newline();
    fontlib_DrawString("THE INVENTORY TO");
    fontlib_Newline();
    fontlib_DrawString("EQUIP IT.");
    fontlib_Newline();
    fontlib_DrawString("KILL THE AIR WIZARD");
    fontlib_Newline();
    fontlib_DrawString("TO WIN THE GAME!");
    fontlib_Newline();
}
