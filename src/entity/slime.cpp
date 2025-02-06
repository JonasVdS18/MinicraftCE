#include "slime.hpp"
#include <debug.h>
#include <sys/util.h>

Slime::Slime(const unsigned int lvl) : Mob(), lvl{lvl}
{
    x = randInt(0, 64 * 16 - 1);
    y = randInt(0, 64 * 16 - 1);
}

Slime::~Slime()
{
}

void Slime::tick()
{
    // dbg_printf("SLIME TICK\n");
    Mob::tick();
}
