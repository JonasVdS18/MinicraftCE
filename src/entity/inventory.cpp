#include "inventory.hpp"
#include "../arraylist.hpp"

Inventory::Inventory() : items{new Arraylist<Item>()}
{
}

Inventory::~Inventory()
{
    delete items;
}

void Inventory::add(Item* item)
{
    items->add(item);
}
/*not fully implemented yet*/
void Inventory::add(int slot, Item* item)
{
    items->add(slot, item);
}
