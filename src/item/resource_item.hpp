#ifndef RESOURCE_ITEM_HPP
#define RESOURCE_ITEM_HPP

#include "item.hpp"
#include "resource/resource.hpp"

class Resource_item : public Item
{
  public:
    Resource_item(Resource* resource);
    Resource_item(Resource* resource, int count);
    ~Resource_item();
    Resource* resource;
    int count;
    void render_icon(int x, int y) override;
    void render_inventory(int x, int y) override;
    bool is_depleted() override;
    bool interact_on(Tile* tile, Level* level, int xt, int yt, Player* player, uint8_t attack_dir) override;
};

#endif
