#ifndef MENU_HPP
#define MENU_HPP

#include "../arraylist.hpp"
#include "../game.hpp"
#include "../input_handler.hpp"
#include "../item/item.hpp"
#include "../linked_list.hpp"
#include <stdint.h>

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
    void render_item_list(int xo, int yo, int x1, int y1, Arraylist<Item>* list_items, int selected);
};
#endif
