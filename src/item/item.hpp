#ifndef ITEM_HPP
#define ITEM_HPP

#include "../level/tile/tile.hpp"
#include "../screen/list_item.hpp"
#include <graphx.h>

class Entity;
class Player;

class Item : public List_item
{
  public:
    char name[10];
    Item();
    virtual ~Item();
    virtual void render_inventory(int x, int y);
    virtual bool interact(Player* player, Entity* entity, uint8_t attack_dir);
    virtual gfx_sprite_t* get_sprite();
    // void onTake(ItemEntity itemEntity)
    virtual void render_icon(int x, int y);
    // boolean interactOn(Tile tile, Level level, int xt, int yt, Player player, uint8_t attack_dir)
    virtual bool is_depleted();
    virtual bool can_attack();
    virtual uint8_t get_attack_damage_bonus(Entity* entity);
    virtual bool matches(Item* item);
    virtual bool interact_on(Tile* tile, Level* level, int xt, int yt, Player* player, uint8_t attack_dir);
};
#endif
