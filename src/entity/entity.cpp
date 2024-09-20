#include "entity.hpp"
#include "item/item.hpp"
#include "item_entity.hpp"
#include "level/tile/tile.hpp"
#include "mob.hpp"
#include "player.hpp"

void Entity::remove()
{
    removed = true;
}

void Entity::init(Level* level)
{
    this->level = level;
}

//       ____ x1,y1
//       |  |
//       |  |
// x0,y0 ----
bool Entity::intersects(int x0, int y0, int x1, int y1)
{
    // if x + radius_x < x0 is true, then the entity is to the left of the rectangle
    // if y + radius_y < y0 is true, then the entity is under the rectangle
    // if x - radius_x > x1 is true, then the entity is to the right of the rectangle
    // if y - radius_y > y1 is true, then the entity is above the rectangle
    // if this is all false then the entity must intersect somewhere
    return !(x + radius_x < x0 || y + radius_y < y0 || x - radius_x > x1 || y - radius_y > y1);
}

bool Entity::blocks(Entity* e)
{
    return false;
}

bool Entity::move(int xa, int ya)
{
    // has to be implemented
}

bool Entity::move2(int xa, int ya)
{
    // has to be implemented
}

bool Entity::is_blockable_by(Mob* mob)
{
    return true;
}

bool Entity::can_swim()
{
    return false;
}

bool Entity::interact(Player* player, Item* item, int attack_dir)
{
    return item->interact(player, this, attack_dir);
}

bool Entity::use(Player* Player, int attack_dir)
{
    return false;
}

int Entity::get_light_radius()
{
    return 0;
}
