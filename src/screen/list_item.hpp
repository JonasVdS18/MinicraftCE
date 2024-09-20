#ifndef LIST_ITEM_HPP
#define LIST_ITEM_HPP
// interface
class List_item
{
  public:
    virtual void render_inventory(int i, int j) = 0; // pure virtual method
};
#endif
