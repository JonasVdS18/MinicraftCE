#ifndef MENU_HPP
#define MENU_HPP

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
    void render_item_list(uint8_t begin_x, uint8_t begin_y, uint8_t box_height, Linked_list<Item>* list_items,
                                  int selected);
};
#endif
