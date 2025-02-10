#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include "../arraylist.hpp"
#include "../item/item.hpp"
#include "../item/resource/resource.hpp"
#include "../item/resource_item.hpp"
#include "../linked_list.hpp"

class Inventory
{
  public:
    Arraylist<Item>* items;
    Inventory();
    ~Inventory();
    void add(Item* item);
    void add(int slot, Item* item);
    int count(Item* item);
    Resource_item* find_resource(Resource* resource);
};

#endif
