#include "menu.hpp"
#include "../game.hpp"
#include "../input_handler.hpp"

Menu::Menu(Game* game, Input_handler* input)
{
    this->input = input;
    this->game = game;
}

void Menu::tick()
{
}

void Menu::render()
{
}
