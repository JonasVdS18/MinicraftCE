#include "entity.hpp"
#include "item/item.hpp"
#include "item_entity.hpp"
#include "level/level.hpp"
#include "level/tile/tile.hpp"
#include "mob.hpp"
#include "player.hpp"

Entity::Entity()
{
<<<<<<< HEAD
    x = 0;
    y = 0;
    radius_x = 6;
    radius_y = 6;
    removed = false;
    level = NULL;
=======
}

Entity::~Entity()
{
>>>>>>> 1ce7690 (stashing item, mob, player, entity, inventory, resource, resourceitem)
}

void Entity::render()
{
}

void Entity::tick()
{
}

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

bool Entity::blocks(Entity* entity)
{
    return false;
}

void Entity::hurt(Mob* mob, int dmg, int attack_dir)
{
}

void Entity::hurt(Tile* tile, int x, int y, int dmg)
{
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

void Entity::touch_item(Item_entity* item_entity)
{
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
