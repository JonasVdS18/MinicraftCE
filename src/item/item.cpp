#include "item.hpp"
#include "../entity/entity.hpp"
#include "../entity/player.hpp"

Item::Item()
{
}

Item::~Item()
{
}

void Item::render_inventory(int x, int y)
{
}

bool Item::interact(Player* player, Entity* entity, int attack_dir)
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

int get_attack_damage_bonus(Entity* entity)
{
    return 0;
}

const char* Item::get_name()
{
    return static_cast<const char*>("");
}

bool Item::matches(Item* item)
{
    return this->get_name() == item->get_name();
}

bool Item::interact_on(Tile* tile, Level* level, int xt, int yt, Player* player, uint8_t attack_dir)
{
    return false;
}

gfx_sprite_t* Item::get_sprite()
{
    return NULL;
}

bool Item::is_depleted()
{
    return false;
}

int Item::get_attack_damage_bonus(Entity* entity)
{
    return 0;
}
