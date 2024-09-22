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

int getAttackDamageBonus(Entity entity)
{
    return 0;
}

char* Item::get_name()
{
    return "";
}

bool Item::matches(Item item)
{
    return this->get_name() == item.get_name();
}
