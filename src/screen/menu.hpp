#ifndef MENU_HPP
#define MENU_HPP

#include "../game.hpp"
#include "../input_handler.hpp"

// #include "../Game.hpp"
class Menu
{
  protected:
    Game* game;
    input_handler* input;

  public:
    Menu(Game* game, input_handler* input);
    void tick();
    void render();
};
#endif
