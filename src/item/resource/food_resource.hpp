#ifndef FOOD_RESOURCE_HPP
#define FOOD_RESOURCE_HPP
#include "resource.hpp"

class Food_resource : public Resource
{
  public:
    Food_resource(char* name, gfx_rletsprite_t* sprite, uint8_t heal, uint8_t stamina_cost);
    ~Food_resource();
    bool interact_on(Tile* tile, Level* level, int xt, int yt, Player* player, uint8_t attack_dir) override;

  private:
    uint8_t heal;
    uint8_t stamina_cost;
};
#endif
