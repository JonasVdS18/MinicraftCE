#include "resource.hpp"
#include "../../gfx/minigfx1.h"
#include "food_resource.hpp"
#include <debug.h>

Resource* Resource::apple = nullptr;

Resource::Resource(char* name, gfx_rletsprite_t* sprite) : name{name}, sprite{sprite}
{
}
Resource::~Resource()
{
}
bool Resource::interact_on(Tile* tile, Level* level, int xt, int yt, Player* player, uint8_t attack_dir)
{
    return false;
}

void Resource::init_resources()
{
    Resource::apple = new Food_resource("APPLE", rlet_apple, 1, 5);
}
