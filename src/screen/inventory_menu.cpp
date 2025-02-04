#include "inventory_menu.hpp"
#include "../entity/player.hpp"
#include "../gfx/gfx.h"
#include "font.hpp"
#include <fontlibc.h>

Inventory_menu::Inventory_menu(Player* player) : Menu(player->game, player->input)
{
    this->player = player;
    if (player->active_item != NULL)
    {
        player->inventory->items->add(0, player->active_item);
        player->active_item = NULL;
    }
}

Inventory_menu::~Inventory_menu()
{
}

void Inventory_menu::tick()
{
    int len = player->inventory->items->size();

    if (input->menu->clicked)
    {
        game->set_menu(NULL);
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
        Item* item = player->inventory->items->remove(selected);
        player->active_item = item;
        game->set_menu(NULL);
    }
}

void Inventory_menu::render()
{
    Font::renderFrame("INVENTORY", 9, 16, 16, 11, 10);
    // Menu::render_item_list(32, 32, (rlet_inventory_screen_height - 16), player->inventory->items, selected);
}
