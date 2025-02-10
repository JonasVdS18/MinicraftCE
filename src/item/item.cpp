#include "item.hpp"
#include "../entity/entity.hpp"
#include "../entity/player.hpp"
#include "debug.h"

Item::Item()
{
    name[0] = '\0';
}

Item::~Item()
{
}

void Item::render_inventory(int x, int y)
{
}

bool Item::interact(Player* player, Entity* entity, uint8_t attack_dir)
{
    return false;
}

gfx_sprite_t* get_sprite()
{
}

void Item::render_icon(int x, int y)
{
}

bool is_depleted()
{
    return false;
}

bool Item::can_attack()
{
    return false;
}

uint8_t get_attack_damage_bonus(Entity* entity)
{
    return 0;
}

bool Item::matches(Item* item)
{
    return this->name == item->name;
}

bool Item::interact_on(Tile* tile, Level* level, int xt, int yt, Player* player, uint8_t attack_dir)
{
    return false;
}

gfx_sprite_t* Item::get_sprite()
{
    return nullptr;
}

bool Item::is_depleted()
{
    return false;
}

uint8_t Item::get_attack_damage_bonus(Entity* entity)
{
    return 0;
}
