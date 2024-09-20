#ifndef MENU_HPP
#define MENU_HPP

#include "../game.hpp"
#include "../input_handler.hpp"

class Menu
{
  protected:
    Game* game;
    Input_handler* input;

  public:
    Menu(Game* game, Input_handler* input);
    virtual void tick();
    virtual void render();
};
#endif
