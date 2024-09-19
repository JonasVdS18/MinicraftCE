#ifndef MENU_HPP
#define MENU_HPP

#include "../game.hpp"
#include "../input_handler.hpp"

// #include "../Game.hpp"
class Menu
{
  protected:
    Game* game;
    Input_handler* input;

  public:
    Menu(Game* game, Input_handler* input);
    void tick();
    void render();
};
#endif
