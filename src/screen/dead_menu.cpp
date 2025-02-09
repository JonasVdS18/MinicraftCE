#include "dead_menu.hpp"
#include "../game.hpp"
#include "font.hpp"
#include "title_menu.hpp"
Dead_menu::Dead_menu(Game* game, Input_handler* input) : Menu(game, input), input_delay{60}
{
}

Dead_menu::~Dead_menu()
{
}
void Dead_menu::tick()
{
    if (input_delay > 0)
        input_delay--; // the inputDelay will minus by 1.
    else if (input->attack->clicked || input->menu->clicked)
    {
        game->set_menu(new Title_menu(this->game, this->input));
    }
}
void Dead_menu::render()
{
    Font::render_frame("", 0, 1, 2, 18, 9);
    Font::draw("YOU DIED! AWW!", 32, 48, 2, 5);

    int seconds = game->game_time / 60; // The current amount of seconds in the game.
    int minutes = seconds / 60;         // The current amount of minutes in the game.
    int hours = minutes / 60;           // The current amount of hours in the game.
    minutes %= 60; // fixes the number of minutes in the game. Without this, 1h 24min would look like: 1h 84min.
    seconds %= 60; // fixes the number of seconds in the game. Without this, 2min 35sec would look like: 2min 155sec.

    Font::draw("TIME:", 32, 80, 2, 5);
    if (hours > 0)
    {
        Font::draw(hours, 1, 112, 80, 6, 5);
        Font::draw("H", 128, 80, 6, 5);
        Font::draw(minutes, 2, 160, 80, 6, 5);
        Font::draw("M", 192, 80, 6, 5);
    }
    else
    {
        Font::draw(minutes, 2, 112, 80, 6, 5);
        Font::draw("M", 144, 80, 6, 5);
        Font::draw(seconds, 2, 176, 80, 6, 5);
        Font::draw("S", 208, 80, 6, 5);
    }
    Font::draw("SCORE:", 32, 96, 2, 5);
    Font::draw(game->player->score, 3, 128, 96, 6, 5);
    Font::draw("PRESS 2ND", 32, 128, 3, 5);
    Font::draw("TO LOSE", 32, 144, 3, 5);
}
