#include "about_menu.hpp"
#include "title_menu.hpp"
#include <fontlibc.h>

// Call the Menu constructor in the initializer list
About_menu::About_menu(Game* game, Input_handler* input) : Menu(game, input)
{
}

About_menu::~About_menu()
{
}

void About_menu::tick()
{
    if (input->attack->clicked || input->menu->clicked)
    {
        game->set_menu(new Title_menu(this->game, this->input));
    }
}

void About_menu::render()
{
    fontlib_ClearWindow();
    fontlib_SetWindowFullScreen();
    fontlib_HomeUp();
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    fontlib_SetColors(2, 0);
    fontlib_DrawString("ABOUT MINICRAFT");
    fontlib_Newline();
    fontlib_Newline();
    fontlib_SetColors(4, 0);
    fontlib_DrawString("MINICRAFT WAS MADE");
    fontlib_Newline();
    fontlib_DrawString("BY MARKUS PERSSON");
    fontlib_Newline();
    fontlib_DrawString("FOR THE 22'ND LUDUM");
    fontlib_Newline();
    fontlib_DrawString("DARE COMPETITION IN");
    fontlib_Newline();
    fontlib_DrawString("DECEMBER 2011.");
    fontlib_Newline();
    fontlib_Newline();
    fontlib_DrawString("IT IS PORTED TO");
    fontlib_Newline();
    fontlib_DrawString("THE TI-84 CALCULATOR");
    fontlib_Newline();
    fontlib_DrawString("BY JONASVDS18 AND");
    fontlib_Newline();
    fontlib_DrawString("WOLFVDS. IT IS");
    fontlib_Newline();
    fontlib_DrawString("AVAILABLE AT GITHUB.");
}
