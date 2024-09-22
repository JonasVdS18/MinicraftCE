#ifndef ITEM_HPP
#define ITEM_HPP

#include "../screen/list_item.hpp"
#include <graphx.h>

class Entity;
class Player;

class Item : public List_item
{
  public:
    Item();
    virtual ~Item();
    virtual void render_inventory(int x, int y);
    virtual bool interact(Player* player, Entity* entity, int attack_dir);
    virtual gfx_sprite_t* get_sprite();
    // void onTake(ItemEntity itemEntity)
    virtual void render_icon(int x, int y);
    // boolean interactOn(Tile tile, Level level, int xt, int yt, Player player, int attackDir)
    virtual bool is_depleted();
    virtual bool can_attack();
    virtual int getAttackDamageBonus(Entity* entity);
    virtual const char* get_name();
    virtual bool matches(Item* item);
};
#endif
