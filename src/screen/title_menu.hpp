#ifndef TITLE_MENU_HPP
#define TITLE_MENU_HPP

#include "../game.hpp"
#include "../input_handler.hpp"
#include "menu.hpp"
#include <stdint.h>

class Title_menu : public Menu
{
  private:
    uint8_t selected;

  public:
    Title_menu(Game* game, Input_handler* input);
    virtual ~Title_menu();
    void tick() override;
    void render() override;
};
#endif
