#ifndef MENU_HPP
#define MENU_HPP

#include "../game.hpp"
#include "../input_handler.hpp"

class Game;

class Menu
{
  protected:
    Game* game;
    Input_handler* input;

  public:
    Menu(Game* game, Input_handler* input);
    virtual ~Menu() = default;
    virtual void tick();
    virtual void render();
};
#endif
