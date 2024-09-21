#include "game.hpp"
#include <graphx.h>

int main()
{
    Game* game{new Game()};
    game->run();
    delete game;
    gfx_End();
    return 0;
}
