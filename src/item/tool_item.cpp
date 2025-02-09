#include "tool_item.hpp"
#include "../gfx/minigfx1.h"
#include "../screen/font.hpp"
#include <string.h>
#include <sys/util.h>

char* Tool_item::LEVEL_NAMES[] = {"WOOD", "ROCK", "IRON", "GOLD", "GEM"};

Tool_item::Tool_item(Tool_type* type, uint8_t level) : Item(), type{type}, level{level}
{
    strcpy(name, LEVEL_NAMES[level]);
    strcat(name, " ");
    strcat(name, type->name);

    switch (level)
    {
    case 0:
        if (type == Tool_type::sword)
            sprite = rlet_sword_wood;
        if (type == Tool_type::axe)
            sprite = rlet_axe_wood;
        if (type == Tool_type::pickaxe)
            sprite = rlet_pickaxe_wood;
        if (type == Tool_type::hoe)
            sprite = rlet_hoe_wood;
        if (type == Tool_type::shovel)
            sprite = rlet_shovel_wood;
        break;
    case 1:
        if (type == Tool_type::sword)
            sprite = rlet_sword_stone;
        if (type == Tool_type::axe)
            sprite = rlet_axe_stone;
        if (type == Tool_type::pickaxe)
            sprite = rlet_pickaxe_stone;
        if (type == Tool_type::hoe)
            sprite = rlet_hoe_stone;
        if (type == Tool_type::shovel)
            sprite = rlet_shovel_stone;
        break;
    case 2:
        if (type == Tool_type::sword)
            sprite = rlet_sword_iron;
        if (type == Tool_type::axe)
            sprite = rlet_axe_iron;
        if (type == Tool_type::pickaxe)
            sprite = rlet_pickaxe_iron;
        if (type == Tool_type::hoe)
            sprite = rlet_hoe_iron;
        if (type == Tool_type::shovel)
            sprite = rlet_shovel_iron;
        break;
    case 3:
        if (type == Tool_type::sword)
            sprite = rlet_sword_gold;
        if (type == Tool_type::axe)
            sprite = rlet_axe_gold;
        if (type == Tool_type::pickaxe)
            sprite = rlet_pickaxe_gold;
        if (type == Tool_type::hoe)
            sprite = rlet_hoe_gold;
        if (type == Tool_type::shovel)
            sprite = rlet_shovel_gold;
        break;
    case 4:
        if (type == Tool_type::sword)
            sprite = rlet_sword_gem;
        if (type == Tool_type::axe)
            sprite = rlet_axe_gem;
        if (type == Tool_type::pickaxe)
            sprite = rlet_pickaxe_gem;
        if (type == Tool_type::hoe)
            sprite = rlet_hoe_gem;
        if (type == Tool_type::shovel)
            sprite = rlet_shovel_gem;
        break;

    default:
        break;
    }
}
Tool_item::~Tool_item()
{
}

void Tool_item::render_icon(int x, int y)
{
    gfx_RLETSprite(sprite, x, y);
}

void Tool_item::render_inventory(int x, int y)
{
    gfx_RLETSprite_NoClip(sprite, x, y);
    Font::draw(name, x + 16, y, 2, 5);
}

bool Tool_item::can_attack()
{
    return true;
}

uint8_t Tool_item::get_attack_damage_bonus(Entity* entity)
{
    if (type == Tool_type::axe)
    {
        return (level + 1) * 2 + randInt(0, 4);
    }
    if (type == Tool_type::sword)
    {
        return (level + 1) * 3 + randInt(0, 2 + level * level * 2);
    }
    return 1;
}

bool Tool_item::matches(Item* item)
{
    if (dynamic_cast<Tool_item*>(item) != nullptr)
    {
        Tool_item* other = (Tool_item*)item;
        if (other->type != type)
            return false;
        if (other->level != level)
            return false;
        return true;
    }
    return false;
}
