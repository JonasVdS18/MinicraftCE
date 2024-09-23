#include "inventory_menu.hpp"
#include "../entity/player.hpp"
#include "../gfx/gfx.h"
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
    fontlib_ClearWindow();
    fontlib_SetWindow(32, 32, (rlet_inventory_screen_width - 16), (rlet_inventory_screen_height - 16));
    fontlib_SetCursorPosition(32, 32);
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    fontlib_SetColors(2, 0);
    gfx_RLETSprite_NoClip(rlet_inventory_screen, 16, 16);
    render_item_list(32, 32, (rlet_inventory_screen_height - 16), player->inventory->items, selected);
}
