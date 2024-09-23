#include "menu.hpp"
#include "../game.hpp"
#include "../input_handler.hpp"
#include "../item/item.hpp"
#include "../linked_list.hpp"
#include <fontlibc.h>

Menu::Menu(Game* game, Input_handler* input)
{
    this->input = input;
    this->game = game;
}

void Menu::tick()
{
}

void Menu::render()
{
}

void Menu::render_item_list(uint8_t begin_x, uint8_t begin_y, uint8_t box_height, Linked_list<Item>* list_items,
                            int selected)
{
    bool render_cursor = true; // Renders the ">" "<" arrows between a name.
    if (selected < 0)
    {
        selected = -selected - 1;
        render_cursor = false;
    }
    int i0 = 0;                  // Beginning variable of the list loop
    int i1 = list_items->size(); // End variable of the list loop
    int displayable_item_size = (box_height / fontlib_GetCurrentFontHeight());
    if (i1 > displayable_item_size) // if the last item to siplay is bigger than the window is able to display
        i1 = displayable_item_size;
    int io = selected - (displayable_item_size / 2); // Middle of the list, (selected item). For scrolling effect
    if (io > list_items->size() - displayable_item_size)
    {
        io = list_items->size() -
             displayable_item_size; // if the middle is coming near the bottom, then the selected will change.
    }
    if (io < 0)
    {
        io = 0; // if the middle is coming near the top, then the selected will change
    }

    for (int i = i0; i < i1; i++)
    {
        list_items->get(i + io)->render_inventory((1 + begin_x) * 16,
                                                  (i + 1 + begin_y) *
                                                      16); // this will render all the items in the inventory
    }

    if (render_cursor)
    {
        fontlib_SetCursorPosition(begin_x, begin_y + fontlib_GetCurrentFontHeight() * selected);
        fontlib_DrawString(">");
        fontlib_SetCursorPosition(begin_x + 80, begin_y + fontlib_GetCurrentFontHeight() * selected);
        fontlib_DrawString(">");
    }
}
