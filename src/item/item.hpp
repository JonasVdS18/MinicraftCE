#ifndef ITEM_HPP
#define ITEM_HPP

#include "entity/entity.hpp"
#include "entity/player.hpp"
#include "screen/list_item.hpp"

class Item : public List_item
{
  public:
    void render_inventory(int x, int y);
    bool interact(Player* player, Entity* entity, int attack_dir);
};
#endif
