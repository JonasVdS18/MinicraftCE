#include "inventory.hpp"
#include "../arraylist.hpp"
#include "../item/item.hpp"
#include "../item/resource_item.hpp"
#include <debug.h>

Inventory::Inventory() : items{new Arraylist<Item>()}
{
}

Inventory::~Inventory()
{
    for (int i = 0; i < items->size(); i++)
    {
        delete items->get(i);
    }

    delete items;
}

void Inventory::add(Item* item)
{
    if (dynamic_cast<Resource_item*>(item) != nullptr)
    {
        dbg_printf("dynamic cast worked\n");
        Resource_item* to_take = static_cast<Resource_item*>(item);
        Resource_item* has = find_resource(to_take->resource);
        if (has == nullptr)
        {
            dbg_printf("hass == nullptr\n");
            items->add(to_take);
        }
        else
        {
            dbg_printf("hass != nullptr\n");
            has->count += to_take->count;
        }
    }
    else
    {
        dbg_printf("dynamic cast didn't work\n");
        items->add(item);
    }
}
/*not fully implemented yet*/
void Inventory::add(int slot, Item* item)
{
    if (dynamic_cast<Resource_item*>(item) != nullptr)
    {
        dbg_printf("dynamic cast worked\n");
        Resource_item* to_take = static_cast<Resource_item*>(item);
        Resource_item* has = find_resource(to_take->resource);
        if (has == nullptr)
        {
            dbg_printf("hass == nullptr\n");
            items->add(slot, to_take);
        }
        else
        {
            dbg_printf("hass != nullptr\n");
            has->count += to_take->count;
        }
    }
    else
    {
        dbg_printf("dynamic cast didn't work\n");
        items->add(slot, item);
    }
}

/** Returns the amount of an item you have in the inventory */
int Inventory::count(Item* item)
{
    if (dynamic_cast<Resource_item*>(item) != nullptr)
    {
        Resource_item* ri = find_resource((static_cast<Resource_item*>(item))->resource);
        if (ri != nullptr)
            return ri->count;
    }
    else
    {
        int count{0};
        for (int i = 0; i < items->size(); i++)
        {
            if (items->get(i)->matches(item))
                count++;
        }
        return count;
    }
    return 0;
}

Resource_item* Inventory::find_resource(Resource* resource)
{
    for (int i = 0; i < items->size(); i++)
    {
        if (dynamic_cast<Resource_item*>(items->get(i)) != nullptr)
        {
            Resource_item* has = static_cast<Resource_item*>(items->get(i));
            if (has->resource == resource)
                return has;
        }
    }
    return nullptr;
}
