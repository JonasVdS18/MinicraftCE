#include "level.hpp"
#include "../arraylist.hpp"
#include "../entity/entity.hpp"
#include "../entity/player.hpp"
#include "../entity/slime.hpp"
#include "../entity/zombie.hpp"
#include "../gfx/minigfx1.h"
#include "../gfx/minigfx2.h"
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
const int SCREEN_WIDTH_IN_TILES_BUFFER{1};
// amount of tiles to buffer around the screen height, this value is multiplied by 2 because it's a buffer under
// and above the screen.
// This is used for the tick to determine which tiles are updated more frequent.
const int SCREEN_HEIGHT_IN_TILES_BUFFER{1};

// The amount of tiles to update frequently (every tick)
// We divide by 50 to have the same update frequency as in the original game
const int AMOUNT_OF_TILES_TO_TICK_FREQUENTLY{(SCREEN_WIDTH_IN_TILES + 2 * SCREEN_WIDTH_IN_TILES_BUFFER) *
                                             (SCREEN_HEIGHT_IN_TILES + 2 * SCREEN_HEIGHT_IN_TILES_BUFFER) / 50};

// The amount of tiles that will be ticked infrequently (not in the view of the player), will be divided by this number
// for performance reasons.
// This is also the tick modifier when calling tick on the tiles to make up for less tick calls.
const int AMOUNT_OF_TILES_TO_TICK_INFREQUENTLY_MODIFIER{20};

// Only entities within a rectangle of 2*ENTITY_TICK_RADIUS_X by 2*ENTITY_TICK_RADIUS_Y will be ticked, this is in pixel
// coordinates
const int ENTITY_TICK_RADIUS_X{32 * 6};

const int ENTITY_TICK_RADIUS_Y{32 * 4};

Level::Level(int width, int height, int8_t level, Level* parent_level)
    : width{width}, height{height}, chunk_size{16},
      width_in_chunks{(uint8_t)((width + (int)chunk_size - 1) / (int)chunk_size)},
      height_in_chunks{(uint8_t)((height + (int)chunk_size - 1) / (int)chunk_size)}, x_offset{0}, y_offset{0},
      monster_density{8}, entities{new Arraylist<Entity>(64)},
      entities_in_chunks{new Arraylist<Entity>*[width_in_chunks * height_in_chunks]},
      screen_entities{new Arraylist<Entity>(12)}, deleted_entities{new Arraylist<Entity>(4)}, player{NULL},
      depth{level}, tick_timer{0}
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
                int r = randInt(0, 1);
                if (r == 0)
                {
                    tiles[i] = Tile::rock->id;
                }
                else
                {
                    tiles[i] = Tile::grass->id;
                }
                data[i] = 0;
            }
        }
    }

    // create the screen tiles that will be rendered
    generate_screen_tiles();
    screen_tiles.map = screen_tiles_map;
    screen_tiles.tiles = mini_tiles_tiles;
    screen_tiles.type_width = gfx_tile_16_pixel;
    screen_tiles.type_height = gfx_tile_16_pixel;
    screen_tiles.tile_height = TILE_HEIGHT;
    screen_tiles.tile_width = TILE_WIDTH;
    screen_tiles.draw_height = TILE_DRAW_HEIGHT;
    screen_tiles.draw_width = TILE_DRAW_WIDTH;
    screen_tiles.height = height * 2;
    screen_tiles.width = width * 2;
    screen_tiles.y_loc = 0;
    screen_tiles.x_loc = 0;
    // create the chunks array

    for (uint8_t i = 0; i < width_in_chunks * height_in_chunks; i++)
    {
        entities_in_chunks[i] = nullptr;
    }

    // try to spawn a lot of mobs so it wont need to spawn a lot when the game has started
    try_spawn(500);

    // Stair code needs to be implemented.

    // Air Wizard code needs to be implemented.
}

Level::~Level()
{
    if (entities_in_chunks != nullptr)
    {
        delete[] entities_in_chunks;
    }
    if (tiles != nullptr)
    {
        delete[] tiles;
    }
    if (data != nullptr)
    {
        delete[] data;
    }
    if (screen_tiles_map != nullptr)
    {
        delete[] screen_tiles_map;
    }
    if (screen_entities != nullptr)
    {
        delete screen_entities;
    }
    if (entities != nullptr)
    {
        // delete all the entities
        for (int i = 0; i < entities->size(); i++)
        {
            Entity* e = entities->remove_index(0);
            delete e;
        }
        delete entities;
    }
    if (deleted_entities != nullptr)
    {
        // delete all the entities
        for (int i = 0; i < deleted_entities->size(); i++)
        {
            Entity* e = deleted_entities->remove_index(0);
            delete e;
        }
        delete deleted_entities;
    }
}

/* This method renders all the tiles in the game */
void Level::render_background(int x_scroll, int y_scroll)
{
    gfx_Tilemap(&screen_tiles, x_scroll, y_scroll);
}

void Level::render_sprites(int x_scroll, int y_scroll)
{
    insertion_sort(screen_entities);
    for (uint8_t i = 0; i < screen_entities->size(); i++)
    {
        screen_entities->get(i)->render(x_scroll, y_scroll);
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
    update_screen_tiles(x, y);
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
    if (dynamic_cast<Player*>(entity) != nullptr)
    {
        if (player != nullptr)
        {
            delete player;
        }
        player = static_cast<Player*>(entity);
    }

    entity->removed = false;
    // add to entities_in_chunks
    int chunk_x = entity->x / (32 * chunk_size);
    int chunk_y = entity->y / (32 * chunk_size);
    if (chunk_x < 0 || chunk_y < 0 || chunk_x >= width_in_chunks || chunk_y >= height_in_chunks)
    {
        return;
    }
    if (entities_in_chunks[chunk_x + chunk_y * width_in_chunks] == nullptr)
    {
        entities_in_chunks[chunk_x + chunk_y * width_in_chunks] = new Arraylist<Entity>();
    }

    entities->add(entity);
    entities_in_chunks[chunk_x + chunk_y * width_in_chunks]->add(entity);
    // if the entity is on screen we add it to the screenentities list
    if (entity->intersects(player->x - ENTITY_TICK_RADIUS_X, player->y - ENTITY_TICK_RADIUS_Y,
                           player->x + ENTITY_TICK_RADIUS_X, player->y + ENTITY_TICK_RADIUS_Y))
        screen_entities->add(entity);

    entity->init(this);
}

// We have to pass the original x and y pixel-coordinates of the entity because it may have changed chunk after tick and
// then we wont find it This does not delete the Entity
void Level::remove(Entity* e)
{
    entities->remove_element(e);
    int chunk_x = e->x / (32 * chunk_size);
    int chunk_y = e->y / (32 * chunk_size);
    if (chunk_x < 0 || chunk_y < 0 || chunk_x >= width_in_chunks || chunk_y >= height_in_chunks)
    {
        return;
    }
    remove_entity(chunk_x + chunk_y * width_in_chunks, e);
    screen_entities->remove_element(e);

    // remove the entity from all the entities that might have it in their nearby list
    // all the entities that are in their nearbylist should also have this entity in their nearby list
    if (e->detectable)
    {
        for (int i = 0; i < e->nearby_entities->size(); i++)
        {
            e->nearby_entities->get(i)->nearby_entities->remove_element(e);
        }
    }

    // delete the entity
    delete e;
}

void Level::remove_entity(uint8_t chunk, Entity* e)
{
    if (chunk < 0 || chunk >= width_in_chunks * height_in_chunks)
    {
        return;
    }
    entities_in_chunks[chunk]->remove_element(e);
}

void Level::insert_entity(uint8_t chunk, Entity* e)
{
    if (chunk < 0 || chunk >= width_in_chunks * height_in_chunks)
    {
        return;
    }
    if (entities_in_chunks[chunk] == nullptr)
    {
        entities_in_chunks[chunk] = new Arraylist<Entity>();
    }
    entities_in_chunks[chunk]->add(e);
}

void Level::try_spawn(int count)
{
    // dbg_printf("TRYSPAWN START\n");
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
            // dbg_printf("SLIME\n");
            mob = new Slime(lvl);
        }
        else
        {
            // dbg_printf("ZOMBIE\n");
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
    // dbg_printf("TRYSPAWN END\n");
}

void Level::tick()
{
    // dbg_printf("Tick Started\n");
    tick_timer++;
    // only spwan every 16 ticks
    if (tick_timer % 16 == 0)
        try_spawn(1);

    // Ticking the tiles
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

    // dbg_printf("ticking entities\n");
    // dbg_printf("entities size: %i\n", entities->size());

    // Only update the screenarray every 8 ticks
    if (tick_timer % 16)
    {
        Arraylist<Entity>* tick_entities{
            get_entities(player->x - ENTITY_TICK_RADIUS_X, player->y - ENTITY_TICK_RADIUS_Y,
                         player->x + ENTITY_TICK_RADIUS_X, player->y + ENTITY_TICK_RADIUS_Y, false)};
        screen_entities->clear();
        screen_entities->add_all(tick_entities);
        delete tick_entities;

        // delete all the entities that need to be deleted.
        // dbg_printf("DELETING the entities\n");
        if (deleted_entities->size() > 0)
        {
            // dbg_printf("deleting 1 entity\n");
            Entity* e = deleted_entities->remove_index(0);
            delete e;
        }
    }

    // int amount = entities->size() > 10 ? 10 : entities->size();
    // dbg_printf("screen_entities size: %i\n", screen_entities->size());
    for (int i = 0; i < screen_entities->size(); i++)
    {
        Entity* e = screen_entities->get(i);
        uint8_t chunk_x_old = e->x / (32 * chunk_size);
        uint8_t chunk_y_old = e->y / (32 * chunk_size);
        int old_chunk = chunk_x_old + chunk_y_old * width_in_chunks;

        e->tick();

        if (e->removed)
        {
            remove(e);
        }
        else
        {
            uint8_t chunk_x_new = e->x / (32 * chunk_size);
            uint8_t chunk_y_new = e->y / (32 * chunk_size);
            int new_chunk = chunk_x_new + chunk_y_new * width_in_chunks;

            if (old_chunk != new_chunk)
            {
                remove_entity(old_chunk, e);
                insert_entity(new_chunk, e);
            }
        }
    }

    // delete tick_entities;

    x_offset = player->x - GFX_LCD_WIDTH / 2 + 16;
    y_offset = player->y - GFX_LCD_HEIGHT / 2 + 32;
}

/* Gets all the entities from a square area of 4 points. The pointer that gets returned has to be DELETED!!!*/
// This functions is very expensive
// also detects entities that are not detectable when only_detectables is true
Arraylist<Entity>* Level::get_entities(int x0, int y0, int x1, int y1, bool only_detectables)
{
    Arraylist<Entity>* result{new Arraylist<Entity>(4)};
    // dbg_printf("in getentities\n");
    //  make this static

    int chunk_x0 = x0 / (32 * chunk_size);
    int chunk_y0 = y0 / (32 * chunk_size);
    int chunk_x1 = x1 / (32 * chunk_size);
    int chunk_y1 = y1 / (32 * chunk_size);

    // clamp the bounds
    if (chunk_x0 < 0)
        chunk_x0 = 0;
    if (chunk_x0 >= width_in_chunks)
        chunk_x0 = width_in_chunks - 1;
    if (chunk_y0 < 0)
        chunk_y0 = 0;
    if (chunk_y0 >= height_in_chunks)
        chunk_y0 = height_in_chunks - 1;

    if (chunk_x1 < 0)
        chunk_x1 = 0;
    if (chunk_x1 >= width_in_chunks)
        chunk_x1 = width_in_chunks - 1;
    if (chunk_y1 < 0)
        chunk_y1 = 0;
    if (chunk_y1 >= height_in_chunks)
        chunk_y1 = height_in_chunks - 1;

    // dbg_printf("after clamp\n");

    for (int i = chunk_x0; i <= chunk_x1; i++)
    {
        for (int j = chunk_y0; j <= chunk_y1; j++)
        {
            if (entities_in_chunks[i + j * width_in_chunks] != nullptr)
            {
                Arraylist<Entity>* entities{entities_in_chunks[i + j * width_in_chunks]};
                const int size{entities->size()};
                for (int k = 0; k < size; k++)
                {
                    Entity* e = entities->get(k);
                    // if we only want detectables and the entity is not detecatble we skip it
                    if (only_detectables && !e->detectable)
                    {
                        continue;
                    }
                    if (e->intersects(x0, y0, x1, y1))
                    {
                        result->add(e);
                    }
                }
            }
        }
    }

    return result; // returns the result list of entities
}

void Level::generate_screen_tiles()
{
    screen_tiles_map = new uint8_t[width * height * 4];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            update_screen_tiles(x, y);
        }
    }
}

void Level::update_screen_tiles(int x, int y) // needs to be called if a tile is changed, x and y in tile coordinates
{
    if (tiles[x + width * y] == Tile::rock->id)
    {
        screen_tiles_map[(x + width * 2 * y) * 2] = 5;
        screen_tiles_map[(x + width * 2 * y) * 2 + 1] = 6;
        screen_tiles_map[(x + width * 2 * y) * 2 + width * 2] = 5 + 16;
        screen_tiles_map[(x + width * 2 * y) * 2 + 1 + width * 2] = 6 + 16;
    }
    if (tiles[x + width * y] == Tile::grass->id)
    {
        bool connected_up = get_tile(x, y - 1)->connects_to_grass;
        bool connected_down = get_tile(x, y + 1)->connects_to_grass;
        bool connected_left = get_tile(x - 1, y)->connects_to_grass;
        bool connected_right = get_tile(x + 1, y)->connects_to_grass;

        if (connected_up)
        {
            if (connected_left)
            {
                screen_tiles_map[(x + width * 2 * y) * 2] = 3;
            }
            else
            {
                screen_tiles_map[(x + width * 2 * y) * 2] = 16;
            }

            if (connected_right)
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + 1] = 4;
            }
            else
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + 1] = 2 + 16;
            }
        }
        else
        {
            if (connected_left)
            {
                screen_tiles_map[(x + width * 2 * y) * 2] = 1;
            }
            else
            {
                screen_tiles_map[(x + width * 2 * y) * 2] = 0;
            }
            if (connected_right)
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + 1] = 1;
            }
            else
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + 1] = 2;
            }
        }

        if (connected_down)
        {
            if (connected_left)
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + width * 2] = 3 + 16;
            }
            else
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + width * 2] = 16;
            }
            if (connected_right)
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + 1 + width * 2] = 4 + 16;
            }
            else
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + 1 + width * 2] = 2 + 16;
            }
        }
        else
        {
            if (connected_left)
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + width * 2] = 1 + 2 * 16;
            }
            else
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + width * 2] = 2 * 16;
            }
            if (connected_right)
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + 1 + width * 2] = 1 + 2 * 16;
            }
            else
            {
                screen_tiles_map[(x + width * 2 * y) * 2 + 1 + width * 2] = 2 + 2 * 16;
            }
        }
    }
}

void Level::insertion_sort(Arraylist<Entity>* arraylist)
{
    if (arraylist->size() == 0)
    {
        return;
    }

    const uint8_t size{arraylist->size()};

    // current is the element we are going to sort, all the elements before
    // current are already sorted
    for (uint8_t current = 1; current < size; current++)
    {
        // index is the index we are going to compare against

        int current_y = arraylist->get(current)->y;

        uint8_t index = current;

        bool found_index = false;

        while (index > 0 && !found_index)
        {
            index--;
            if (arraylist->get(index)->y < current_y)
            {
                found_index = true;
            }
        }
        // no elemnt is smaller then this one
        if (!found_index)
        {
            arraylist->add(0, arraylist->remove_index(current));
            continue;
        }
        // if this is the largest element we wont insert it
        if (index + 1 == current)
        {
            continue;
        }
        // we insert the elements
        else
        {
            arraylist->add(index + 1, arraylist->remove_index(current));
        }
    }
}
