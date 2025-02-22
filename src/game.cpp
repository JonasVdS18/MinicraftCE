#include "game.hpp"
#include "gfx/minigfx1.h"
#include "gfx/minigfx2.h"
#include "item/resource/food_resource.hpp"
#include "item/resource_item.hpp"
#include "item/tool_item.hpp"
#include "level/level.hpp"
#include "screen/dead_menu.hpp"
#include "screen/font.hpp"
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
    // dbg_printf("IN SETMENU\n");
    if (this->menu != nullptr)
    {
        // dbg_printf("DELETING PREVIOUS MENU\n");
        delete this->menu;
    }
    this->menu = menu;
}

Game::Game()
    : game_time{0}, has_won{false}, menu{nullptr}, player{nullptr}, running{true}, level{nullptr}, tick_count{0},
      player_dead_time{0}, pending_level_change{0}, won_timer{0}, current_level{3}, prev_health{0}, prev_stamina{0},
      input{new Input_handler()}, last_clock{clock()}, clockdiff{0}, score{0}
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
    last_clock = clock();
    clockdiff = 0;
    int frames{0};
    int ticks{0};

    if (init())
    {
        stop();
    }

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

bool Game::init()
{
    // dbg_printf("INIT START\n");

    if (minigfx1_init() == 0)
    {
        return 1;
    }
    Resource::init_resources();

    if (minigfx2_init() == 0)
    {
        return 1;
    }

    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    fontlib_font_t* mini_font;
    mini_font = fontlib_GetFontByIndex("MINIFONT", 0);
    if (mini_font == nullptr)
    {
        gfx_PrintStringXY("MINIFONT appvar not found or invalid", 0, 0);
        return 1;
    }

    fontlib_SetFont(mini_font, static_cast<fontlib_load_options_t>(0));
    fontlib_SetTransparency(false);
    fontlib_SetLineSpacing(1, 1);
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);

    gfx_SetClipRegion(0, 0, GFX_LCD_WIDTH, GFX_LCD_HEIGHT - 32);
    srand(rtc_Time());

    set_menu(new Title_menu(this, input));
    return 0;
}

void Game::reset()
{
    gfx_SetDrawScreen();
    gfx_ZeroScreen();
    fontlib_SetColors(2, 0);
    fontlib_SetWindowFullScreen();
    fontlib_SetCursorPosition(0, 120);
    Font::print_centered("LOADING WORLD...");
    // dbg_printf("RESET\n");
    running = true;
    tick_count = 0;
    game_time = 0;
    player_dead_time = 0;
    pending_level_change = 0;
    won_timer = 0;
    has_won = false;
    current_level = 3;
    prev_health = 0;
    prev_stamina = 0;
    score = 0;

    // placeholder level
    input->reset();
    if (level != nullptr)
    {
        delete level;
        level = nullptr;
    }
    level = new Level(80, 80, 0, nullptr);
    player = new Player(this, input);
    player->inventory->add(new Tool_item(Tool_type::sword, 4));
    /*player->inventory->add(new Tool_item(Tool_type::sword, 0));
    player->inventory->add(new Tool_item(Tool_type::sword, 1));
    player->inventory->add(new Tool_item(Tool_type::sword, 2));
    player->inventory->add(new Tool_item(Tool_type::sword, 3));
    player->inventory->add(new Tool_item(Tool_type::sword, 4));
    player->inventory->add(new Tool_item(Tool_type::sword, 0));
    player->inventory->add(new Tool_item(Tool_type::sword, 1));
    player->inventory->add(new Tool_item(Tool_type::sword, 4));
    player->inventory->add(new Tool_item(Tool_type::sword, 2));
    player->inventory->add(new Tool_item(Tool_type::sword, 4));
    player->inventory->add(new Tool_item(Tool_type::sword, 3));
    player->inventory->add(new Tool_item(Tool_type::sword, 0));
    player->inventory->add(new Tool_item(Tool_type::sword, 0));
    player->inventory->add(new Tool_item(Tool_type::sword, 1));*/
    player->inventory->add(new Resource_item(Resource::apple));
    player->inventory->add(new Resource_item(Resource::apple));
    player->inventory->add(new Resource_item(Resource::wood));
    player->find_start_pos(level);
    level->add(player);

    // clear everything
    gfx_ZeroScreen();
    gfx_SetDrawBuffer();
    gfx_ZeroScreen();
    input->reset();

    // reset time so we wont lag
    clock_t now_clock{clock()};
    last_clock = now_clock;
}

void Game::start()
{
    // dbg_printf("START\n");
    running = true;
    run();
}

void Game::stop()
{
    // dbg_printf("STOP\n");
    running = false;
}

void Game::tick()
{
    // dbg_printf("TICK START\n");
    tick_count++;
    if (player != NULL)
    {
        if (!player->removed && !has_won)
        {
            game_time++;
        }
    }
    input->tick();
    if (input->quit->clicked)
    {
        stop();
    }

    if (menu != nullptr)
    {
        menu->tick();
    }
    else
    {
        if (player != nullptr)
        {
            if (player->removed)
            {
                player_dead_time++;
                score = player->score;
                player = nullptr;
            }
            /*else if (pending_level_change != 0)
            {

            }*/
        }
        if (player == nullptr && player_dead_time > 0)
        {
            player_dead_time++;
            if (player_dead_time > 60)
            {
                set_menu(new Dead_menu(this, input));
            }
        }
        /*if (won_timer > 0)
        {
            won_timer--;
            if (won_timer == 0)
            {
                set_menu(new Woon_menu(game, input));
            }

        }*/
        if (level != nullptr)
        {
            // player->tick(); // player has to be ticked first
            level->tick();
        }
        Tile::tick_count++;
    }
}

void Game::render()
{
    // dbg_printf("RENDER START\n");
    if (level != nullptr)
    {
        level->render_background(level->x_offset, level->y_offset);
        // player->render(level->x_offset, level->y_offset);
        level->render_sprites(level->x_offset, level->y_offset);
    }
    render_GUI();

    gfx_SwapDraw();
}

void Game::schedule_level_change(int dir)
{
    // dbg_printf("SCHEDULE_LEVEL_CHANGE START\n");
    pending_level_change = dir;
}

void Game::won()
{
    // dbg_printf("WON\n");
    won_timer = 60 * 3;
    has_won = true;
}

void Game::render_GUI()
{
    // dbg_printf("RENDER_GUI START\n");
    if (player != nullptr)
    {
        if (player->health > prev_health)
        {
            for (uint8_t i = player->health - prev_health; i > 0; i--)
            {
                gfx_SetDrawScreen();
                gfx_Sprite_NoClip(heart_full, (prev_health + i - 1) * 16, GFX_LCD_HEIGHT - 32);
                gfx_SetDrawBuffer();
                gfx_Sprite_NoClip(heart_full, (prev_health + i - 1) * 16, GFX_LCD_HEIGHT - 32);
            }
        }
        else if (player->health < prev_health)
        {
            for (uint8_t i = prev_health - player->health; i > 0; i--)
            {
                gfx_SetDrawScreen();
                gfx_Sprite_NoClip(heart_empty, (player->health + i - 1) * 16, GFX_LCD_HEIGHT - 32);
                gfx_SetDrawBuffer();
                gfx_Sprite_NoClip(heart_empty, (player->health + i - 1) * 16, GFX_LCD_HEIGHT - 32);
            }
        }
        if (player->stamina_recharge_delay > 0)
        {
            if (player->stamina_recharge_delay / 4 % 2 == 0)
            {
                for (uint8_t i = 0; i < 10; i++)
                {
                    gfx_SetDrawScreen();
                    gfx_Sprite_NoClip(stamina_blink, i * 16, GFX_LCD_HEIGHT - 16);
                    gfx_SetDrawBuffer();
                    gfx_Sprite_NoClip(stamina_blink, i * 16, GFX_LCD_HEIGHT - 16);
                }
            }
            else
            {
                for (uint8_t i = 0; i < 10; i++)
                {
                    gfx_SetDrawScreen();
                    gfx_Sprite_NoClip(stamina_empty, i * 16, GFX_LCD_HEIGHT - 16);
                    gfx_SetDrawBuffer();
                    gfx_Sprite_NoClip(stamina_empty, i * 16, GFX_LCD_HEIGHT - 16);
                }
            }
        }
        else
        {
            if (player->stamina > prev_stamina)
            {
                for (uint8_t i = player->stamina - prev_stamina; i > 0; i--)
                {
                    gfx_SetDrawScreen();
                    gfx_Sprite_NoClip(stamina_full, (prev_stamina + i - 1) * 16, GFX_LCD_HEIGHT - 16);
                    gfx_SetDrawBuffer();
                    gfx_Sprite_NoClip(stamina_full, (prev_stamina + i - 1) * 16, GFX_LCD_HEIGHT - 16);
                }
            }
            else if (player->stamina < prev_stamina)
            {
                for (uint8_t i = prev_stamina - player->stamina; i > 0; i--)
                {
                    gfx_SetDrawScreen();
                    gfx_Sprite_NoClip(stamina_empty, (player->stamina + i - 1) * 16, GFX_LCD_HEIGHT - 16);
                    gfx_SetDrawBuffer();
                    gfx_Sprite_NoClip(stamina_empty, (player->stamina + i - 1) * 16, GFX_LCD_HEIGHT - 16);
                }
            }
            prev_health = player->health;
            prev_stamina = player->stamina;
        }
    }

    if (menu != nullptr)
    {
        menu->render();
    }
}
