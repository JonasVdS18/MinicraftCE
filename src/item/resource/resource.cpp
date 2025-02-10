#include "resource.hpp"
#include "../../gfx/minigfx1.h"
#include "food_resource.hpp"
#include <debug.h>

Resource* Resource::apple = nullptr;
Resource* Resource::wood = nullptr;
Resource* Resource::cloth = nullptr;
Resource* Resource::stone = nullptr;
Resource* Resource::wheat = nullptr;
Resource* Resource::bread = nullptr;
Resource* Resource::coal = nullptr;
Resource* Resource::iron_ore = nullptr;
Resource* Resource::gold_ore = nullptr;
Resource* Resource::iron_ingot = nullptr;
Resource* Resource::gold_ingot = nullptr;
Resource* Resource::slime = nullptr;
Resource* Resource::glass = nullptr;
Resource* Resource::gem = nullptr;

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
    Resource::wood = new Resource("WOOD", rlet_wood);
    Resource::stone = new Resource("STONE", rlet_stone);
    Resource::wheat = new Resource("WHEAT", rlet_wheat);
    Resource::bread = new Food_resource("BREAD", rlet_bread, 2, 5);
    Resource::apple = new Food_resource("APPLE", rlet_apple, 1, 5);
    Resource::coal = new Resource("COAL", rlet_coal);
    Resource::iron_ore = new Resource("I.ORE", rlet_iron_ore);
    Resource::gold_ore = new Resource("G.ORE", rlet_gold_ore);
    Resource::iron_ingot = new Resource("IRON", rlet_iron);
    Resource::gold_ingot = new Resource("GOLD", rlet_gold);
    Resource::slime = new Resource("SLIME", rlet_slime_ball);
    Resource::glass = new Resource("GLASS", rlet_glass);
    Resource::cloth = new Resource("CLOTH", rlet_cloth);
    Resource::gem = new Resource("GEM", rlet_gem_ore);
}
