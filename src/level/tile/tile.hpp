#ifndef TILE_HPP
#define TILE_HPP

#include <stdint.h>

class Entity;
class Level;
class Mob;
class Player;
class Item;

class Tile
{
  public:
    static int tick_count;
    static Tile* tiles[256];
    static Tile* grass;
    static Tile* rock;
    static Tile* water;
    static Tile* lava;
    static Tile* stairs_down;
    static Tile* stairs_up;

    const uint8_t id;

    bool connects_to_grass;
    bool connects_to_sand;
    bool connects_to_lava;
    bool connects_to_water;

    Tile(uint8_t id);

    virtual bool may_pass(Level* level, int x, int y, Entity* e);
    virtual int get_light_radius(Level* level, int x, int y);
    virtual void hurt(Level* level, int x, int y, Mob* source, uint8_t damage, uint8_t attack_dir);
    virtual void bumped_into(Level* level, int xt, int yt, Entity* entity);
    virtual void tick(Level* level, int xt, int yt, uint8_t modifier);
    virtual void stepped_on(Level* level, int xt, int yt, Entity* entity);
    virtual bool interact(Level* level, int xt, int yt, Player* player, Item* item, uint8_t attack_dir);
    virtual bool connects_to_liquid();
};
#endif
