#include "zombie.hpp"
#include <sys/util.h>

Zombie::Zombie(const unsigned int lvl) : Mob(), lvl{lvl}
{
    x = randInt(0, 64 * 16 - 1);
    y = randInt(0, 64 * 16 - 1);
}

Zombie::~Zombie()
{
}
