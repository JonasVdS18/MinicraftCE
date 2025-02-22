#include "inventory_menu.hpp"
#include "../entity/player.hpp"
#include "../gfx/minigfx1.h"
#include "font.hpp"
#include <debug.h>
#include <fontlibc.h>

Inventory_menu::Inventory_menu(Player* player) : Menu(player->game, player->input), player{player}, selected{0}
{
    if (player->active_item != nullptr)
    {
        // dbg_printf("before add\n");
        player->inventory->items->add(0, player->active_item);
        // dbg_printf("before after\n");
        player->active_item = nullptr;
    }
}

Inventory_menu::~Inventory_menu()
{
}

void Inventory_menu::tick()
{
    // dbg_printf("IN INVENTORY TICK\n");
    int len = player->inventory->items->size();
    // dbg_printf("AFTER SIZE\n");

    if (input->menu->clicked)
    {
        // dbg_printf("LEAVING INVENTORY\n");
        game->set_menu(nullptr);
    }

    if (input->up->clicked)
        selected--;
    if (input->down->clicked)
        selected++;

    if (len == 0)
        selected = 0;

    if (selected < 0)
        selected += len;
    if (selected >= len)
        selected -= len;

    if (input->attack->clicked && len > 0)
    {
        Item* item = player->inventory->items->remove_index(selected);
        player->active_item = item;
        game->set_menu(nullptr);
    }
}

void Inventory_menu::render()
{
    Font::render_frame("INVENTORY", 9, 1, 1, 12, 11);
    render_item_list(1, 1, 12, 11, player->inventory->items, selected);
}
