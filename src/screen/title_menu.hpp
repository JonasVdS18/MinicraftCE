#ifndef TITLE_MENU_HPP
#define TITLE_MENU_HPP
#include "menu.hpp"

class Title_menu : public Menu
{
  private:
    uint8_t selected;
    const char* options[3];

  public:
    Title_menu(Game* game, Input_handler* input);
    void tick() override;
    void render() override;
};
#endif
