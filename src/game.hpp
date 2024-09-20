#ifndef GAME_HPP
#define GAME_HPP
#include "screen/menu.hpp"

#include "input_handler.hpp"

class Game
{
  public:
    int game_time;
    bool has_won;
    Menu* menu;
    Game();
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
    int tick_count;
    int player_dead_time;
    int pending_level_change;
    int wontimer;
    int current_level;
    Input_handler* input;

    void init();
    void render_GUI();
};

#endif
