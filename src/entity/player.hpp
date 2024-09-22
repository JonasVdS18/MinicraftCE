#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../game.hpp"
#include "../input_handler.hpp"
#include "../item/item.hpp"
#include "inventory.hpp"
#include "mob.hpp"
#include <stdint.h>

class Player : public Mob
{
  private:
    Input_handler* input;
    int attack_time;
    uint8_t attack_dir;
    int on_stair_delay;

  public:
    Game* game;
    Inventory* inventory;
    Item* attack_item;
    Item* active_item;
    uint8_t stamina;
    uint8_t stamina_recharge;
    uint8_t stamina_recharge_delay;
    const uint8_t max_stamina;
    int invulnerable_time;
    Player(Game* game, Input_handler* input);
    ~Player();
};
#endif
