#ifndef ITEM_HPP
#define ITEM_HPP

#include "../screen/list_item.hpp"

class Entity;
class Player;

class Item : public List_item
{
  public:
    void render_inventory(int x, int y);
    bool interact(Player* player, Entity* entity, int attack_dir);
};
#endif
