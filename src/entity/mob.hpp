#ifndef MOB_HPP
#define MOB_HPP

#include "../level/level.hpp"
#include "entity.hpp"
#include <stdint.h>

class Level;

class Mob : public Entity
{
  protected:
    int walk_dist;
    uint8_t dir; // The direction the mob is facing, used in attacking and rendering. 0 is down, 1 is up, 2 is left, 3
                 // is right
    int8_t x_knockback, y_knockback;
    virtual void die();
    virtual bool is_swimming();
    virtual void do_hurt(uint8_t damage, uint8_t attack_dir);

  public:
    int8_t hurt_time;
    int8_t maxhealth;
    int8_t health;
    uint8_t swim_timer;
    int tick_time;
    Mob();
    ~Mob();
    virtual void tick() override;
    virtual bool move(int xa, int ya) override;
    virtual bool blocks(Entity* entity) override;
    virtual void hurt(Mob* mob, int damage, int attack_dir) override;
    virtual void hurt(Tile* tile, int x, int y, int damage) override;
    virtual void heal(uint8_t heal);
    virtual bool find_start_pos(Level* level);
};

#endif
