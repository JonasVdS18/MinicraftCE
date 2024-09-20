#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "level/level.hpp"

class Mob;
class Item_entity;
class Player;
class Item;
class Tile;

class Entity
{
  public:
    int x, y;
    int radius_x, radius_y;
    bool removed;
    Level* level;
    virtual void render();
    virtual void tick();
    virtual void remove();
    virtual void init(Level* level) final;
    // Checks if the entity intersects 4 points
    virtual bool intersects(int x0, int y0, int x1, int y1);
    virtual bool blocks(Entity* e);
    virtual void hurt(Mob* mob, int dmg, int attack_dir);
    virtual void hurt(Tile* tile, int x, int y, int dmg);
    virtual bool move(int xa, int ya);
    virtual bool move2(int xa, int ya);
    virtual bool is_blockable_by(Mob* mob);
    virtual void touch_item(Item_entity* item_entity);
    virtual bool can_swim();
    virtual bool interact(Player* player, Item* item, int attack_dir);
    virtual bool use(Player* player, int attack_dir);
    virtual int get_light_radius();

  protected:
    virtual void touched_by(Entity* entity);
};
#endif
