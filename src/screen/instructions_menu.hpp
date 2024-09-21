#ifndef INSTRUCTIONS_MENU_HPP
#define INSTRUCTIONS_MENU_HPP

#include "../game.hpp"
#include "../input_handler.hpp"
#include "menu.hpp"

class Instructions_menu : public Menu
{

  public:
    Instructions_menu(Game* game, Input_handler* input);
    virtual ~Instructions_menu();
    void tick() override;
    void render() override;
};
#endif
