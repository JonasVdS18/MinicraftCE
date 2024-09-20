#ifndef TITLE_MENU_HPP
#define TITLE_MENU_HPP
#include "menu.hpp"

class Title_menu : public Menu
{
  private:
    uint8_t selected;

  public:
    Title_menu(Game* game, Input_handler* input);
    void tick() override;
    void render() override;
};
#endif
