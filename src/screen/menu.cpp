#include "menu.hpp"
#include "../arraylist.hpp"
#include "../game.hpp"
#include "../input_handler.hpp"
#include "../item/item.hpp"
#include "../linked_list.hpp"
#include "font.hpp"
#include <debug.h>
#include <fontlibc.h>

Menu::Menu(Game* game, Input_handler* input) : game{game}, input{input}
{
}

void Menu::tick()
{
}

void Menu::render()
{
}

// box_height in pixels
void Menu::render_item_list(int xo, int yo, int x1, int y1, Arraylist<Item>* list_items, int selected)
{
    bool render_cursor = true; // Renders the ">" "<" arrows between a name.
    if (selected < 0)
    {
        selected = -selected - 1;
        render_cursor = false;
    }
    int w = x1 - xo;             // Width variable determined by given values
    int h = y1 - yo - 1;         // Height variable determined by given values
    int i0 = 0;                  // Beginning variable of the list loop
    int i1 = list_items->size(); // End variable of the list loop
    if (i1 > h)
        i1 = h; // If the end variable is larger than the height variable, then end variable will equal height variable.
    int io = selected - h / 2; // Middle of the list, (selected item). For scrolling effect
    if (io > list_items->size() - h)
        io = list_items->size() - h; // if the middle is coming near the bottom, then the selected will change.
    if (io < 0)
        io = 0; // if the middle is coming near the top, then the selected will change

    for (int i = i0; i < i1; i++)
    {
        list_items->get(i + io)->render_inventory((1 + xo) * 16,
                                                  (i + 1 + yo) * 16); // this will render all the items in the inventory
    }

    if (render_cursor)
    {
        int yy = selected + 1 - io + yo; // the y position of the currently selected item
        Font::draw(">", (xo + 0) * 16, yy * 16, 2, 5);
        Font::draw("<", (xo + w) * 16, yy * 16, 2, 5);
    }
}
