#ifndef TOOL_ITEM_HPP
#define TOOL_ITEM_HPP
#include "item.hpp"
#include "tool_type.hpp"
#include <graphx.h>

class Tool_item : public Item
{
  public:
    Tool_item(Tool_type* type, uint8_t level);
    ~Tool_item();
    static char* LEVEL_NAMES[];
    Tool_type* type;
    uint8_t level;
    gfx_rletsprite_t* sprite;
    void render_icon(int x, int y) override;
    void render_inventory(int x, int y) override;
    bool can_attack() override;
    uint8_t get_attack_damage_bonus(Entity* entity) override;
    bool matches(Item* item) override;
};

#endif
