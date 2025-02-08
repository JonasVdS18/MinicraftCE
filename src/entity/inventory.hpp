#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include "../arraylist.hpp"
#include "../item/item.hpp"
#include "../linked_list.hpp"

class Inventory
{
  public:
    Arraylist<Item>* items;
    Inventory();
    ~Inventory();
    void add(Item* item);
    void add(int slot, Item* item);
};

#endif
