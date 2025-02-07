#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../item/item.hpp"
#include "../level/level.hpp"
#include "../level/tile/tile.hpp"

class Mob;
class Item_entity;
class Player;
class Item;
class Tile;
class Level;

class Entity
{
  public:
    int x, y;
    int8_t radius_x, radius_y;
    bool removed;
    Level* level;
    Arraylist<Entity>* nearby_entities;
    Entity();
    virtual ~Entity();
    virtual void render(int x_scroll, int y_scroll);
    virtual void tick();
    virtual void remove();
    virtual void init(Level* level) final;
    // Checks if the entity intersects 4 points
    inline bool intersects(int x0, int y0, int x1, int y1);
    virtual bool blocks(Entity* entity);
    virtual void hurt(Mob* mob, uint8_t damage, uint8_t attack_dir);
    virtual void hurt(Tile* tile, int x, int y, uint8_t damage);
    virtual bool move(int xa, int ya);
    virtual bool move2(int xa, int ya);
    virtual bool is_blockable_by(Mob* mob);
    virtual void touch_item(Item_entity* item_entity);
    virtual bool can_swim();
    virtual bool interact(Player* player, Item* item, uint8_t attack_dir);
    virtual bool use(Player* player, uint8_t attack_dir);
    virtual uint8_t get_light_radius();
    virtual void touched_by(Entity* entity);
};

//       ____ x1,y1
//       |  |
//       |  |
// x0,y0 ----
inline bool Entity::intersects(int x0, int y0, int x1, int y1)
{
    // if x + radius_x < x0 is true, then the entity is to the left of the rectangle
    // if y + radius_y < y0 is true, then the entity is under the rectangle
    // if x - radius_x > x1 is true, then the entity is to the right of the rectangle
    // if y - radius_y > y1 is true, then the entity is above the rectangle
    // if this is all false then the entity must intersect somewhere
    return !(x + radius_x < x0 || y + radius_y < y0 || x - radius_x > x1 || y - radius_y > y1);
}

#endif
