#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include "../../level/level.hpp"
#include <graphx.h>

class Resource
{
  public:
    Resource(char* name, gfx_rletsprite_t* sprite);
    ~Resource();
    char* name;
    gfx_rletsprite_t* sprite;
    virtual bool interact_on(Tile* tile, Level* level, int xt, int yt, Player* player, uint8_t attack_dir);
    // has to be called after the graphics are initialized otherwise the sprites will be fucked up (adresses will be
    // wrong)
    static void init_resources();
    static Resource* wood;
    static Resource* stone;
    static Resource* wheat;
    static Resource* bread;
    static Resource* apple;
    static Resource* coal;
    static Resource* iron_ore;
    static Resource* gold_ore;
    static Resource* iron_ingot;
    static Resource* gold_ingot;
    static Resource* slime;
    static Resource* glass;
    static Resource* cloth;
    static Resource* gem;
};

#endif
