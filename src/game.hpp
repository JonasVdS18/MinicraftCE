#ifndef GAME_HPP
#define GAME_HPP

#include "entity/player.hpp"
#include "input_handler.hpp"
#include "screen/menu.hpp"

class Menu;
class Level;

class Game
{
  public:
    int game_time;
    bool has_won;
    Menu* menu;
    Player* player;
    Game();
    ~Game();
    void set_menu(Menu* menu);
    void run();
    void reset();
    void start();
    void stop();
    void tick();
    void render();
    void schedule_level_change(int dir);
    void won();

  private:
    bool running;
    Level* level;
    int tick_count;
    int player_dead_time;
    int pending_level_change;
    int wontimer;
    int current_level;
    uint8_t prev_health, prev_stamina;
    Input_handler* input;

    void init();
    void render_GUI();
};

#endif
