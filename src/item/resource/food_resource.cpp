#include "food_resource.hpp"
#include "../../entity/player.hpp"
#include <debug.h>

Food_resource::Food_resource(char* name, gfx_rletsprite_t* sprite, uint8_t heal, uint8_t stamina_cost)
    : Resource(name, sprite), heal{heal}, stamina_cost{stamina_cost}
{
}
Food_resource::~Food_resource()
{
}

bool Food_resource::interact_on(Tile* tile, Level* level, int xt, int yt, Player* player, uint8_t attack_dir)
{
    if (player->health < player->maxhealth && player->pay_stamina(stamina_cost))
    {
        player->heal(heal);
        return true;
    }
    return false;
}
