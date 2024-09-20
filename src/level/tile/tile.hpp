#ifndef TILE_HPP
#define TILE_HPP
#include "../../entity/entity.hpp"
#include "../../entity/mob.hpp"
#include "../../entity/player.hpp"
#include "../level.hpp"
#include <stdint.h>

class Tile
{
  public:
    static int tickCount;
    static Tile* tiles[256];

    const uint8_t id;

    bool connects_to_grass;
    bool connects_to_sand;
    bool connects_to_lava;
    bool connects_to_water;

    Tile(uint8_t _id);

    virtual void render(Level* level, int x, int y);
    virtual bool may_pass(Level* level, int x, int y, Entity* e);
    virtual int get_light_radius(Level* level, int x, int y);
    virtual void hurt(Level* level, int x, int y, Mob* source, int dmg, int attack_dir);
    virtual void bumped_into(Level* level, int xt, int yt, Entity* entity);
    virtual void tick(Level* level, int xt, int yt);
    virtual void stepped_on(Level* level, int xt, int yt, Entity* entity);
    virtual bool interact(Level* level, int xt, int yt, Player* player, Item* item, int attack_dir);
    virtual bool connects_to_liquid();
};
#endif
