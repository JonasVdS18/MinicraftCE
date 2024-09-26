#include "level.hpp"
#include "../entity/entity.hpp"
#include "../entity/player.hpp"
#include "../entity/slime.hpp"
#include "../entity/zombie.hpp"
#include "../gfx/gfx.h"
#include "../linked_list.hpp"
#include "tile/tile.hpp"
#include <debug.h>
#include <stdint.h>
#include <sys/util.h>

Level::Level(int width, int height, int level, Level* parent_level)
    : depth{level}, width{width}, height{height}, monster_density{8}, entities{new Linked_list<Entity>()}, player{NULL}
{
    // 2D array
    uint8_t** maps = NULL;

    // Level gen needs to be imlemented here.

    if (maps != NULL)
    {
        tiles = maps[0];
        data = maps[1];
    }
    else
    {
        /*
        tiles = NULL;
        data = NULL;*/

        // placeholder level
        tiles = new uint8_t[width * height];
        data = new uint8_t[width * height];

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int i = x + y * width;
                tiles[i] = Tile::rock->id;
                data[i] = 0;
            }
        }
    }

    // Stair code needs to be implemented.

    // Air Wizard code needs to be implemented.
}

Level::~Level()
{
    if (entities != nullptr)
    {
        delete entities;
    }
    if (tiles != nullptr)
    {
        delete[] tiles;
    }
    if (data != nullptr)
    {
        delete[] data;
    }
}

/* This method renders all the tiles in the game */
void Level::render_background(int x_scroll, int y_scroll)
{
    int xo = x_scroll >> 5;             // the game's horizontal scroll offset in tile coordinates.
    int yo = y_scroll >> 5;             // the game's vertical scroll offset in tile coordinates.
    int w = (GFX_LCD_WIDTH + 32) >> 5;  // width of the screen being rendered in tile coordinates
    int h = (GFX_LCD_HEIGHT + 32) >> 5; // height of the screen being rendered in tile coordinates
    for (int y = yo; y <= h + yo; y++)
    {
        for (int x = xo; x <= w + xo; x++)
        {
            // x * 32 - x_scroll is the screen coordinate.
            get_tile(x, y)->render(
                this, x * 32 - x_scroll,
                y * 32 - y_scroll); // renders the tile on the screen using screen cooridinates not tile coordinates.
        }
    }
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
        Mob* mob{nullptr};
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
        const unsigned int lvl{randInt(0, max_level - min_level) + min_level};
        // dbg_printf("LVL: %i\n", lvl);
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
            // dbg_printf("FOUND START POS\n");
            add(mob);
        }
        else
        {
            // dbg_printf("DELETED MOB\n");
            delete mob;
        }
    }
}

void Level::tick()
{
    // dbg_printf("LEVEL::TICKED CALLED\n");
    try_spawn(1);
    // dbg_printf("LEVEL::TICKED END\n");
    for (int i = 0; i < width * height / 50; i++)
    {
        int xt = randInt(0, width - 1);
        int yt = randInt(0, height - 1);
        get_tile(xt, yt)->tick(this, xt, yt);
    }

    int size{entities->size()};
    Entity** entities_array{entities->to_array()};

    for (int i = 0; i < size; i++)
    {
        Entity* e = entities_array[i];

        e->tick(); // calls the entity's tick() method.

        if (e->removed)
        {
            entities->remove(e);
            delete e;
        }
    }

    delete[] entities_array;
}

/* Gets all the entities from a square area of 4 points. The pointer that gets returned has to be DELETED!!!*/
Linked_list<Entity>* Level::get_entities(int x0, int y0, int x1, int y1)
{
    // dbg_printf("IN GET_ENTITIES\n");
    //  dbg_printf("START OF GET_ENTITIES\n");
    Linked_list<Entity>* result{new Linked_list<Entity>()};
    int size{entities->size()};
    Entity** entities_array{entities->to_array()};
    for (int i = 0; i < size; i++)
    {
        Entity* e = entities_array[i];
        if (e->intersects(x0, y0, x1, y1))
            result->add(e);
    }

    delete[] entities_array;
    // dbg_printf("AMOUNT OF ENTITIES IN GET_ENTITIES: %i\n", result->size());
    return result; // returns the result list of entities
}
