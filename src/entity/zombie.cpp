#include "zombie.hpp"
#include <sys/util.h>

Zombie::Zombie(int lvl) : Mob()
{
    this->lvl = lvl;
    x = randInt(0, 64 * 16 - 1);
    y = randInt(0, 64 * 16 - 1);
}
