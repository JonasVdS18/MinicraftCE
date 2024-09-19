#include "game.hpp"
#include <keypadc.h>

int main()
{
    Game* game{new Game()};
    game->run();
    return 0;
}
