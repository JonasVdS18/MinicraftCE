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

// amount of tiles in the screen width.
const int SCREEN_WIDTH_IN_TILES{GFX_LCD_WIDTH >> 5};
// amount of tiles in the screen height.
const int SCREEN_HEIGHT_IN_TILES{GFX_LCD_HEIGHT >> 5};
// amount of tiles to buffer around the screen width, this value is multiplied by 2 because it's a buffer to the left
// and right f the screen.
// This is used for the tick to determine which tiles are updated more frequent.
const int SCREEN_WIDTH_IN_TILES_BUFFER{3};
// amount of tiles to buffer around the screen height, this value is multiplied by 2 because it's a buffer under
// and above the screen.
// This is used for the tick to determine which tiles are updated more frequent.
const int SCREEN_HEIGHT_IN_TILES_BUFFER{2};

// The amount of tiles to update frequently (every tick)
// We divide by 50 to have the same update frequency as in the original game
const int AMOUNT_OF_TILES_TO_TICK_FREQUENTLY{(SCREEN_WIDTH_IN_TILES + 2 * SCREEN_WIDTH_IN_TILES_BUFFER) *
                                             (SCREEN_HEIGHT_IN_TILES + 2 * SCREEN_HEIGHT_IN_TILES_BUFFER) / 50};

// The amount of tiles that will be ticked infrequently (not in the view of the player), will be divided by this number
// for performance reasons.
// This is also the tick modifier when calling tick on the tiles to make up for less tick calls.
const int AMOUNT_OF_TILES_TO_TICK_INFREQUENTLY_MODIFIER{20};

Level::Level(int width, int height, int level, Level* parent_level)
    : depth{level}, width{width}, height{height}, x_offset{0}, y_offset{0}, monster_density{8},
      entities{new Linked_list<Entity>()}, player{NULL}
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
    int w = (GFX_LCD_WIDTH) >> 5;       // width of the screen being rendered in tile coordinates
    int h = (GFX_LCD_HEIGHT - 32) >> 5; // height of the screen being rendered in tile coordinates
    for (int y = yo; y <= h + yo; y++)
    {
        for (int x = xo; x <= w + xo; x++)
        {
            // x * 32 - x_scroll is the screen coordinate.
            get_tile(x, y)->render(this, x,
                                   y); // renders the tile on the screen using tile cooridinates not screen coordinates.
        }
    }
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
    // this is expensive
    try_spawn(1);
    // dbg_printf("LEVEL::TICKED END\n");

    // Update the tiles that are viewed by the player frequently
    // const int tiles_to_update_per_tick{static_cast<int>(width * height / 50)};

    int tiles_tick_amount{0};

    for (int i = 0; i < AMOUNT_OF_TILES_TO_TICK_FREQUENTLY; i++)
    {
        int xt = randInt(player->x - SCREEN_WIDTH_IN_TILES / 2 - SCREEN_WIDTH_IN_TILES_BUFFER,
                         player->x + SCREEN_WIDTH_IN_TILES / 2 + SCREEN_WIDTH_IN_TILES_BUFFER);
        int yt = randInt(player->y - SCREEN_HEIGHT_IN_TILES / 2 - SCREEN_HEIGHT_IN_TILES_BUFFER,
                         player->y + SCREEN_HEIGHT_IN_TILES / 2 + SCREEN_HEIGHT_IN_TILES_BUFFER);
        get_tile(xt, yt)->tick(this, xt, yt, 1);
        tiles_tick_amount++;
    }

    // Update the tiles that are not visible less frequent but in larger increments.
    const int AMOUNT_OF_TILES_TO_TICK_INFREQUENTLY{(width * height - AMOUNT_OF_TILES_TO_TICK_FREQUENTLY) / 50 /
                                                   AMOUNT_OF_TILES_TO_TICK_INFREQUENTLY_MODIFIER};

    if (AMOUNT_OF_TILES_TO_TICK_INFREQUENTLY > 0)
    {
        for (int i = 0; i < AMOUNT_OF_TILES_TO_TICK_INFREQUENTLY; i++)
        {
            int xt = randInt(0, width - 1 - SCREEN_WIDTH_IN_TILES - SCREEN_WIDTH_IN_TILES_BUFFER * 2);
            int yt = randInt(0, height - 1 - SCREEN_HEIGHT_IN_TILES - SCREEN_HEIGHT_IN_TILES_BUFFER * 2);
            if (xt >= player->x - SCREEN_WIDTH_IN_TILES / 2 - SCREEN_WIDTH_IN_TILES_BUFFER)
            {
                xt += SCREEN_WIDTH_IN_TILES_BUFFER * 2 + SCREEN_WIDTH_IN_TILES;
            }
            if (yt >= player->y - SCREEN_HEIGHT_IN_TILES / 2 - SCREEN_HEIGHT_IN_TILES_BUFFER)
            {
                yt += SCREEN_HEIGHT_IN_TILES_BUFFER * 2 + SCREEN_HEIGHT_IN_TILES;
            }
            get_tile(xt, yt)->tick(this, xt, yt, AMOUNT_OF_TILES_TO_TICK_INFREQUENTLY_MODIFIER);
            tiles_tick_amount++;
        }
    }

    int size{entities->size()};
    dbg_printf("ENTITIES: %i\n", size);
    /*
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

    delete[] entities_array;*/

    x_offset = player->x - GFX_LCD_WIDTH / 2 + 16;
    y_offset = player->y - GFX_LCD_HEIGHT / 2 + 32;
}

/* Gets all the entities from a square area of 4 points. The pointer that gets returned has to be DELETED!!!*/
// This functions is very expensive
Linked_list<Entity>* Level::get_entities(int x0, int y0, int x1, int y1)
{
    // dbg_printf("IN GET_ENTITIES\n");
    // dbg_printf("START OF GET_ENTITIES\n");
    Linked_list<Entity>* result{new Linked_list<Entity>()};
    const int size{entities->size()};
    // to array seems to be very expensive especially for large lists
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
