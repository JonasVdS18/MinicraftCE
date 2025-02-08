#ifndef DEAD_MENU_HPP
#define DEAD_MENU_HPP
#include "menu.hpp"
class Dead_menu : public Menu
{
  public:
    Dead_menu(Game* game, Input_handler* input);
    ~Dead_menu();
    void tick() override;
    void render() override;

  private:
    int8_t input_delay;
};
#endif
