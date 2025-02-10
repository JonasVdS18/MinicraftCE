#include "resource_item.hpp"
#include "../gfx/minigfx1.h"
#include "../screen/font.hpp"
#include <debug.h>
#include <string.h>

Resource_item::Resource_item(Resource* resource) : Item(), resource{resource}, count{1}
{
    strcpy(name, resource->name);
}
Resource_item::Resource_item(Resource* resource, int count) : Item(), resource{resource}, count{count}
{
    strcpy(name, resource->name);
}
Resource_item::~Resource_item()
{
}

bool Resource_item::is_depleted()
{
    return count <= 0;
}

void Resource_item::render_icon(int x, int y)
{
    gfx_RLETSprite(resource->sprite, x, y);
}

void Resource_item::render_inventory(int x, int y)
{
    gfx_RLETSprite_NoClip(resource->sprite, x, y);
    Font::draw(name, x + 64, y, 2, 5);
    int cc = count;
    if (cc > 999)
        cc = 999;
    Font::draw(cc, x + 16, y, 2, 5);
}

bool Resource_item::interact_on(Tile* tile, Level* level, int xt, int yt, Player* player, uint8_t attack_dir)
{
    dbg_printf("in resourceitem interact\n");
    if (resource->interact_on(tile, level, xt, yt, player, attack_dir))
    {
        dbg_printf("actually payed\n");
        count--;
        return true;
    }
    return false;
}
