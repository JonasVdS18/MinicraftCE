#include "inventory_menu.hpp"
#include "../entity/player.hpp"
#include "../gfx/minigfx1.h"
#include "font.hpp"
#include <debug.h>
#include <fontlibc.h>

Inventory_menu::Inventory_menu(Player* player) : Menu(player->game, player->input)
{
    // dbg_printf("CREATING NEW INVENTORY MENU\n");
    this->player = player;
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

    if (input->up->clicked && selected > 0)
    {
        selected--;
    }
    if (input->down->clicked && selected < len)
    {
        selected++;
    }

    if (input->attack->clicked && len > 0)
    {
        Item* item = player->inventory->items->remove_index(selected);
        player->active_item = item;
        game->set_menu(nullptr);
    }
}

void Inventory_menu::render()
{
    Font::renderFrame("INVENTORY", 9, 16, 16, 11, 10);
}
