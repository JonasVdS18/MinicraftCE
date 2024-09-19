#include "game.hpp"
#include "gfx/gfx.h"
#include <graphx.h>
#include <sys/rtc.h>
#include <time.h>

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
}

void Game::run()
{
    clock_t last_clock{clock()};
    double unprocessed{0};
    // amount of seconds per tick.
    const double seconds_per_tick{1 / 60};
    int frames{0};
    int ticks{0};

    init();

    while (running)
    {
        clock_t now_clock{clock()};
        //((now_clock - last_clock) / CLOCKS_PER_SEC) gives the aount of seconds that have passed
        unprocessed += ((now_clock - last_clock) / CLOCKS_PER_SEC) / seconds_per_tick;
        last_clock = now_clock;

        bool should_render{false};

        while (unprocessed > 1)
        {
            ticks++;
            tick();
            unprocessed -= 1;
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
