#include "menu.hpp"
#include "../game.hpp"
#include "../input_handler.hpp"

Menu::Menu(Game* game, input_handler* input)
{
    this->input = input;
    this->game = game;
}
