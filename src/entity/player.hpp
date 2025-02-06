#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../input_handler.hpp"
#include "../item/item.hpp"
#include "inventory.hpp"
#include "mob.hpp"
#include <stdint.h>
class Game;

class Player : public Mob
{
  private:
    int attack_time;
    uint8_t attack_dir;
    int on_stair_delay;
    bool use();
    bool use(int x0, int y0, int x1, int y1);
    void attack();
    bool interact(int x0, int y0, int x1, int y1);
    void hurt(int x0, int y0, int x1, int y1);
    uint8_t get_attack_damage(Entity* entity);

  protected:
    void die() override;
    void do_hurt(uint8_t damage, uint8_t attack_dir) override;

  public:
    Game* game;
    Input_handler* input;
    Inventory* inventory;
    Item* active_item;
    Item* attack_item;
    const uint8_t max_stamina;
    uint8_t stamina;
    uint8_t stamina_recharge;
    uint8_t stamina_recharge_delay;
    uint8_t invulnerable_time;
    int score;
    Player(Game* game, Input_handler* input);
    ~Player();
    void tick() override;
    void render(int x_scroll, int y_scroll) override;
    void change_level(int8_t dir);
    void touch_item(Item_entity* item_entity) override;
    bool can_swim() override;
    bool find_start_pos(Level* level) override;
    bool pay_stamina(uint8_t cost);
    uint8_t get_light_radius() override;
    void touched_by(Entity* entity) override;
    void game_won();
};
#endif
