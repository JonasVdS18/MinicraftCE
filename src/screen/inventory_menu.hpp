#ifndef INVENTORY_MENU_HPP
#define INVENTORY_MENU_HPP

#include "../entity/player.hpp"
#include "menu.hpp"

class Inventory_menu : public Menu
{
  private:
    Player* player;
    int selected;

  public:
    Inventory_menu(Player* player);
    ~Inventory_menu();
    void tick() override;
    void render() override;
};

#endif
