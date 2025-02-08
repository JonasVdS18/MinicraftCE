#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "../arraylist.hpp"
#include "tile/tile.hpp"
#include <graphx.h>
#include <stdint.h>

#define TILE_HEIGHT 16
#define TILE_WIDTH 16
#define TILE_DRAW_WIDTH 21
#define TILE_DRAW_HEIGHT 14

// const int MAX_ENTITIES{100};
class Entity;
class Tile;
class Player;

class Level
{
  public:
    // Width and Height in tiles not in pixels.
    const int width, height;
    // size in tiles of a chunk, a chunk is chunksize* chunksize in tiles, its a square with chunksize as length
    const uint8_t chunk_size;
    // Width and height in chunks not in
    const uint8_t width_in_chunks, height_in_chunks;
    // x_offset and y_offset in world coordinates
    int x_offset, y_offset;
    // array of tile id's
    uint8_t* tiles;
    uint8_t* data;
    gfx_tilemap_t screen_tiles; // tilemap object of the actual tiles that will be drawn to the screen
    uint8_t* screen_tiles_map;  // map of the tilemap that belongs to the tilemap object
    int monster_density;
    // Array containing all entities
    Arraylist<Entity>* entities;
    //  Array containing lists of entities per chunks of chunksize * chunksize
    Arraylist<Entity>** entities_in_chunks;
    // Array of entities on screen, these will be ticked and drawn
    Arraylist<Entity>* screen_entities;
    Arraylist<Entity>* deleted_entities;
    Player* player;

    Level(int width, int height, int8_t level, Level* parent_level);
    ~Level();

    void render_background(int x_scroll, int y_scroll);
    void render_sprites(int x_scroll, int y_scroll);
    inline Tile* get_tile(int x, int y);
    void set_tile(int x, int y, Tile* t, uint8_t dataval);
    uint8_t get_data(int x, int y);
    void set_data(int x, int y, uint8_t val);
    // Only used for adding new entities not for swapping chunks
    void add(Entity* entity);
    // Removes the entity form a chunk
    void remove(Entity* e);
    // Inserts the Entity in a chunk
    void insert_entity(uint8_t chunk, Entity* e);
    void remove_entity(uint8_t chunk, Entity* e);
    void try_spawn(int count);
    void tick();
    Arraylist<Entity>* get_entities(int x0, int y0, int x1, int y1);

  private:
    int8_t depth;
    unsigned int tick_timer;
    void generate_screen_tiles();
    void update_screen_tiles(int x,
                             int y); // needs to be called if a tile is changed, x and y in tile coordinates
    void insertion_sort(Arraylist<Entity>* arraylist);
};

inline Tile* Level::get_tile(int x, int y)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
    {
        return Tile::rock;
    }
    return Tile::tiles[tiles[x + y * width]];
}

#endif
