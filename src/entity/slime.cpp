#include "slime.hpp"
#include <sys/util.h>

Slime::Slime(const unsigned int lvl) : Mob(), lvl{lvl}
{
    x = randInt(0, 64 * 16 - 1);
    y = randInt(0, 64 * 16 - 1);
}

Slime::~Slime()
{
}
