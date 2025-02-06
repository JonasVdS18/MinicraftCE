#include "entity.hpp"
#include "item/item.hpp"
#include "item_entity.hpp"
#include "level/level.hpp"
#include "level/tile/tile.hpp"
#include "mob.hpp"
#include "player.hpp"
#include <debug.h>

Entity::Entity() : x{0}, y{0}, radius_x{6}, radius_y{6}, removed{false}, level{NULL}
{
}

Entity::~Entity()
{
}

void Entity::render(int x_scroll, int y_scroll)
{
}

void Entity::tick()
{
    // dbg_printf("ENTITY TICK\n");
}

void Entity::remove()
{
    removed = true;
}

void Entity::init(Level* level)
{
    this->level = level;
}

bool Entity::blocks(Entity* entity)
{
    return false;
}

void Entity::hurt(Mob* mob, int damage, int attack_dir)
{
}

void Entity::hurt(Tile* tile, int x, int y, int damage)
{
}

bool Entity::move(int xa, int ya)
{
    if (xa != 0 || ya != 0)
    {
        bool stopped = true;
        if (xa != 0 && move2(xa, 0))
        {
            stopped = false;
        }
        if (ya != 0 && move2(0, ya))
        {
            stopped = false;
        }
        if (!stopped)
        {

            int x_tile = x >> 5;
            int y_tile = y >> 5;
            level->get_tile(x_tile, y_tile)->stepped_on(level, x_tile, y_tile, this);
        }
        return !stopped;
    }
    return true;
}

bool Entity::move2(int xa, int ya)
{
    int xto0 = ((x)-radius_x) >> 5;   // gets the tile coordinate of the position to the left of the sprite
    int yto0 = ((y)-radius_y) >> 5;   // gets the tile coordinate of the position to the top of the sprite
    int xto1 = ((x) + radius_x) >> 5; // gets the tile coordinate of the position to the right of the sprite
    int yto1 = ((y) + radius_y) >> 5; // gets the tile coordinate of the position to the bottom of the sprite

    int xt0 = ((x + xa) - radius_x) >>
              5; // gets the tile coordinate of the position to the left of the sprite + the horizontal acceleration
    int yt0 = ((y + ya) - radius_y) >>
              5; // gets the tile coordinate of the position to the top of the sprite + the vertical acceleration
    int xt1 = ((x + xa) + radius_x) >>
              5; // gets the tile coordinate of the position to the right of the sprite + the horizontal acceleration
    int yt1 = ((y + ya) + radius_y) >>
              5; // gets the tile coordinate of the position to the bottom of the sprite + the vertical acceleration

    bool blocked = false; // determines if the next tile can block you.
    for (int yt = yt0; yt <= yt1; yt++)
        for (int xt = xt0; xt <= xt1; xt++)
        {
            if (xt >= xto0 && xt <= xto1 && yt >= yto0 && yt <= yto1)
            {
                continue;
            }

            level->get_tile(xt, yt)->bumped_into(level, xt, yt, this);
            if (!level->get_tile(xt, yt)->may_pass(level, xt, yt, this))
            {
                blocked = true;
                return false;
            }
        }
    if (blocked)
    {
        return false;
    }

    /*
    Arraylist<Entity>* was_inside =
        level->get_entities(x - radius_x, y - radius_y, x + radius_x,
                            y + radius_y); // gets all of the entities that are inside this entity (aka: colliding)
    */
    Arraylist<Entity>* is_inside =
        level->get_entities(x + xa - radius_x, y + ya - radius_y, x + xa + radius_x,
                            y + ya + radius_y); // gets the entities that this entity will touch.

    /*
    int is_inside_size{is_inside->size()};
    for (int i = 0; i < is_inside_size; i++)
    {
        Entity* entity = is_inside->get(i);
        if (entity == this)
        {
            continue;
        }

        entity->touched_by(this);
    }
    // is_inside->remove_all(was_inside);
    for (int i = 0; i < is_inside_size; i++)
    {
        Entity* entity = is_inside->get(i);
        if (entity == this)
        {
            continue;
        }

        if (entity->blocks(this))
        {
            delete was_inside;
            delete is_inside;
            return false;
        }
    }
    */

    int is_inside_size{is_inside->size()};
    for (int i = 0; i < is_inside_size; i++)
    {
        Entity* entity = is_inside->get(i);
        if (entity == this)
        {
            continue;
        }

        entity->touched_by(this);

        if (entity->blocks(this))
        {
            // delete was_inside;
            delete is_inside;
            return false;
        }
    }

    x += xa;
    y += ya;

    // delete was_inside;
    delete is_inside;

    return true;
}

void Entity::touched_by(Entity* entity)
{
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

uint8_t Entity::get_light_radius()
{
    return 0;
}
