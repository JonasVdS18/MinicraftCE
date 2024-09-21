#ifndef ABOUT_MENU_HPP
#define ABOUT_MENU_HPP

#include "../game.hpp"
#include "../input_handler.hpp"
#include "menu.hpp"

class About_menu : public Menu
{

  public:
    About_menu(Game* game, Input_handler* input);
    virtual ~About_menu();
    void tick() override;
    void render() override;
};
#endif
