#include "game.hpp"
#include "fonts/fonts.h"
#include "gfx/gfx.h"
#include "level/level.hpp"
#include "screen/menu.hpp"
#include "screen/title_menu.hpp"
#include <debug.h>
#include <fontlibc.h>
#include <graphx.h>
#include <sys/rtc.h>
#include <time.h>

// Amount of ticks per second.
const clock_t TICK_RATE{60};
const clock_t CLOCKS_PER_TICK{CLOCKS_PER_SEC / TICK_RATE};

void Game::set_menu(Menu* menu)
{
    if (this->menu != NULL)
    {
        delete this->menu;
    }
    this->menu = menu;
}

Game::Game()
    : running{true}, tick_count{0}, prev_health{0}, prev_stamina{0}, game_time{0}, player_dead_time{0},
      pending_level_change{0}, wontimer{0}, has_won{false}, current_level{3}, input{new Input_handler()}, menu{NULL},
      level{NULL}, player{NULL}
{
}

Game::~Game()
{
    delete menu;
    delete input;
    delete level;
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
            if (tick_count % 60 == 0)
            {
                dbg_printf("SECONDS: %i\n", static_cast<int>(tick_count / 60));
            }
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
    gfx_SetDrawBuffer();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    fontlib_SetFont(reinterpret_cast<const fontlib_font_t*>(FONT), static_cast<fontlib_load_options_t>(0));
    fontlib_SetTransparency(true);
    fontlib_SetLineSpacing(1, 1);
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    gfx_SetClipRegion(0, 0, GFX_LCD_WIDTH, GFX_LCD_HEIGHT - 48);
    srand(rtc_Time());

    set_menu(new Title_menu(this, input));
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

    // placeholder level
    level = new Level(20, 20, 0, NULL);
    player = new Player(this, input);
    player->find_start_pos(level);
    level->add(player);
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
    if (input->quit->clicked)
    {
        stop();
    }

    if (menu != NULL)
    {
        menu->tick();
    }
    else
    {
        if (level != NULL)
        {
            level->tick();
            player->tick();
        }
        Tile::tick_count++;
    }
}

void Game::render()
{

    if (level != NULL)
    {
        level->render_background(level->x_offset, level->y_offset);
        player->render(level->x_offset, level->y_offset);
    }
    else
    {
        gfx_ZeroScreen();
    }
    render_GUI();

    gfx_SwapDraw();
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
    if (player != NULL)
    {
        if (player->health > prev_health)
        {
            for (uint8_t i = player->health - prev_health; i > 0; i--)
            {
                gfx_SetDrawScreen();
                gfx_Sprite_NoClip(heart_full, (prev_health + i - 1) * 16, GFX_LCD_HEIGHT - 48);
                gfx_SetDrawBuffer();
                gfx_Sprite_NoClip(heart_full, (prev_health + i - 1) * 16, GFX_LCD_HEIGHT - 48);
            }
        }
        else if (player->health < prev_health)
        {
            for (uint8_t i = prev_health - player->health; i > 0; i--)
            {
                gfx_SetDrawScreen();
                gfx_Sprite_NoClip(heart_empty, (player->health + i - 1) * 16, GFX_LCD_HEIGHT - 48);
                gfx_SetDrawBuffer();
                gfx_Sprite_NoClip(heart_empty, (player->health + i - 1) * 16, GFX_LCD_HEIGHT - 48);
            }
        }
        if (player->stamina > prev_stamina)
        {
            for (uint8_t i = player->stamina - prev_stamina; i > 0; i--)
            {
                gfx_SetDrawScreen();
                gfx_Sprite_NoClip(stamina_full, (prev_stamina + i - 1) * 16, GFX_LCD_HEIGHT - 32);
                gfx_SetDrawBuffer();
                gfx_Sprite_NoClip(stamina_full, (prev_stamina + i - 1) * 16, GFX_LCD_HEIGHT - 32);
            }
        }
        else if (player->stamina < prev_stamina)
        {
            for (uint8_t i = prev_stamina - player->stamina; i > 0; i--)
            {
                gfx_SetDrawScreen();
                gfx_Sprite_NoClip(stamina_empty, (player->stamina + i - 1) * 16, GFX_LCD_HEIGHT - 32);
                gfx_SetDrawBuffer();
                gfx_Sprite_NoClip(stamina_empty, (player->stamina + i - 1) * 16, GFX_LCD_HEIGHT - 32);
            }
        }
        prev_health = player->health;
        prev_stamina = player->stamina;
    }

    if (menu != NULL)
    {
        menu->render();
    }
}
