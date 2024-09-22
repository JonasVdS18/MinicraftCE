#include "level.hpp"
#include "../entity/entity.hpp"
#include "../entity/player.hpp"
#include "../entity/slime.hpp"
#include "../entity/zombie.hpp"
#include "../linked_list.hpp"
#include "tile/tile.hpp"
#include <stdint.h>
#include <sys/util.h>

Level::Level(int width, int height, int level, Level* parent_level)
{
    depth = level;
    this->width = width;
    this->height = height;
    monster_density = 8;
    // 2D array
    uint8_t** maps = NULL;
    entities = new Linked_list<Entity>();

    // Level gen needs to be imlemented here.

    if (maps != NULL)
    {
        tiles = maps[0];
        data = maps[1];
    }

    // Stair code needs to be implemented.

    // Air Wizard code needs to be implemented.
}

Tile* Level::get_tile(int x, int y)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
    {
        return Tile::rock;
    }
    return Tile::tiles[tiles[x + y * width]];
}

void Level::set_tile(int x, int y, Tile* t, uint8_t dataval)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
    {
        return;
    }

    tiles[x + y * width] = t->id;
    data[x + y * width] = dataval;
}

uint8_t Level::get_data(int x, int y)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
    {
        return 0;
    }
    return data[x + y * width];
}

void Level::set_data(int x, int y, uint8_t val)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
    {
        return;
    }
    data[x + y * width] = val;
}

void Level::add(Entity* entity)
{
    if (dynamic_cast<Player*>(entity) != NULL)
    {
        if (player != NULL)
        {
            delete player;
        }
        player = static_cast<Player*>(entity);
    }

    entity->removed = false;
    // add to entities
    entities->add(entity);
    entity->init(this);
}

void Level::remove(Entity* e)
{
    entities->remove(e);
}

void Level::try_spawn(int count)
{
    for (int i = 0; i < count; i++)
    {
        Mob* mob;
        int min_level{1}; // minimum level of the mob
        int max_level{1}; // maximum level of the mob
        if (depth < 0)
        {
            max_level = (-depth) + 1;
        }
        if (depth < 0)
        {
            min_level = max_level = 4;
        }
        // Not max_level - min_level + 1, because randInt is inclusive.
        int lvl{static_cast<int>(0, max_level - min_level) + min_level};
        if (randInt(0, 1) == 0)
        {
            mob = new Slime(lvl);
        }
        else
        {
            mob = new Zombie(lvl);
        }
        if (mob->find_start_pos(this))
        {
            add(mob);
        }
        else
        {
            delete mob;
        }
    }
}

void Level::tick()
{
    try_spawn(1);
    for (int i = 0; i < width * height / 50; i++)
    {
        int xt = randInt(0, width - 1);
        int yt = randInt(0, height - 1);
        get_tile(xt, yt)->tick(this, xt, yt);
    }
    for (int i = 0; i < entities->size(); i++)
    {
        Entity* e = entities->get(i);

        e->tick(); // calls the entity's tick() method.

        if (e->removed)
        {
            entities->remove(e);
            delete e;
        }
    }
}

Linked_list<Entity>* Level::get_entities(int x0, int y0, int x1, int y1)
{
    return NULL;
}
