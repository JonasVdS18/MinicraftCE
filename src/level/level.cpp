#include "level.hpp"
#include "../entity/entity.hpp"
#include "../entity/player.hpp"
#include "../entity/slime.hpp"
#include "../entity/zombie.hpp"
#include "../gfx/gfx.h"
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
    player = NULL;

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

    entities_in_tiles = new Linked_list<Entity>*[width * height]();
    for (int i = 0; i < width * height; i++)
    {
        entities_in_tiles[i] = new Linked_list<Entity>();
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
    if (entities_in_tiles != nullptr)
    {
        delete[] entities_in_tiles;
    }
}

/* This method renders all the tiles in the game */
void Level::render_background(int x_scroll, int y_scroll)
{
    int xo = x_scroll >> 5;             // the game's horizontal scroll offset in tile coordinates.
    int yo = y_scroll >> 5;             // the game's vertical scroll offset in tile coordinates.
    int w = (GFX_LCD_WIDTH + 31) >> 5;  // width of the screen being rendered in tile coordinates
    int h = (GFX_LCD_HEIGHT + 31) >> 5; // height of the screen being rendered in tile coordinates
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

    // >> 5 to change to tile coordinates (divides by 32)
    insert_entity(entity->x >> 5, entity->y >> 5, entity);
}

void Level::remove(Entity* e)
{
    entities->remove(e);
    // >> 5 to change to tile coordinates (divides by 32)
    remove_entity(e->x >> 5, e->y >> 5, e);
}

void Level::insert_entity(int x, int y, Entity* e)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
    {
        return;
    }
    entities_in_tiles[x + y * width]->add(e);
}

void Level::remove_entity(int x, int y, Entity* e)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
    {
        return;
    }
    entities_in_tiles[x + y * width]->remove(e);
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
        int lvl{static_cast<int>(randInt(0, max_level - min_level) + min_level)};
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
        // The original tile-coordinates of the entity before the tick.
        int xto = e->x >> 5;
        int yto = e->y >> 5;

        e->tick(); // calls the entity's tick() method.

        if (e->removed)
        {
            entities->remove(e);
            remove_entity(e->x >> 5, e->y >> 5, e);
            delete e;
        }
        else
        {
            // The current tile-coordinates of the entity.
            int xt = e->x >> 5; // gets the entity's x coordinate
            int yt = e->y >> 5; // gets the entity's y coordinate

            // If the entity changed tiles we have to update the entity_in_tile list.
            if (xto != xt || yto != yt)
            {
                remove_entity(xto, yto, e);
                insert_entity(xt, yt, e);
            }
        }
    }
}

/* Gets all the entities from a square area of 4 points. */
Linked_list<Entity>* Level::get_entities(int x0, int y0, int x1, int y1)
{
    Linked_list<Entity>* result{new Linked_list<Entity>()};
    int xt0{(x0 >> 5) - 1}; // location of x0 in tile-coordinates.
    int yt0{(y0 >> 5) - 1}; // location of y0 in tile-coordinates.
    int xt1{(x1 >> 5) + 1}; // location of x1 in tile-coordinates.
    int yt1{(y1 >> 5) + 1}; // location of y1 in tile-coordinates.
    for (int y = yt0; y <= yt1; y++)
    { // Loops through the difference between y0 and y1
        for (int x = xt0; x <= xt1; x++)
        { // Loops through the difference between x0 & x1
            if (x < 0 || y < 0 || x >= width || y >= height)
                continue; // if the x & y position is outside the world, then skip the rest of this loop.
            Linked_list<Entity>* entities = entities_in_tiles[x + y * this->width];
            for (int i = 0; i < entities->size(); i++)
            {
                Entity* e = entities->get(i);
                if (e->intersects(x0, y0, x1, y1))
                    result->add(e);
            }
        }
    }
    return result; // returns the result list of entities
}
