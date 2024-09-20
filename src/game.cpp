#include "game.hpp"
#include "fonts/fonts.c"
#include "gfx/gfx.h"
<<<<<<< HEAD
=======
#include <debug.h>
#include <fontlibc.h>
>>>>>>> 7040248 (created a font and worked on the menus)
#include <graphx.h>
#include <sys/rtc.h>
#include <time.h>

// Amount of ticks per second.
const clock_t TICK_RATE{60};
const clock_t CLOCKS_PER_TICK{CLOCKS_PER_SEC / TICK_RATE};

void Game::set_menu(Menu* menu)
{
    this->menu = menu;
}

Game::Game()
{
    running = true;
    tick_count = 0;
    game_time = 0;
    player_dead_time = 0;
    pending_level_change = 0;
    wontimer = 0;
    has_won = false;
    current_level = 3;
    input = new Input_handler();
}

void Game::run()
{
    clock_t last_clock{clock()};
    clock_t clockdiff{0};
    int frames{0};
    int ticks{0};

    init();

    while (running)
    {
        clock_t now_clock{clock()};
        clockdiff += now_clock - last_clock;
        last_clock = now_clock;

        bool should_render{false};

        while (clockdiff > CLOCKS_PER_TICK)
        {
            ticks++;
            tick();
            clockdiff -= CLOCKS_PER_TICK;
            should_render = true;
        }

        if (should_render)
        {
            frames++;
            render();
        }
    }
}

void Game::init()
{
    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    fontlib_SetFont(reinterpret_cast<const fontlib_font_t*>(FONT_data), static_cast<fontlib_load_options_t>(0));
    fontlib_SetTransparency(true);
    srand(rtc_Time());
}

void Game::reset()
{
    running = true;
    tick_count = 0;
    game_time = 0;
    player_dead_time = 0;
    pending_level_change = 0;
    wontimer = 0;
    has_won = false;
    current_level = 3;
}

void Game::start()
{
    running = true;
    run();
}

void Game::stop()
{
    running = false;
}

void Game::tick()
{
    tick_count++;
    input->tick();
}

void Game::render()
{
}

void Game::schedule_level_change(int dir)
{
    pending_level_change = dir;
}

void Game::won()
{
    wontimer = 60 * 3;
    has_won = true;
}

void Game::render_GUI()
{
}
