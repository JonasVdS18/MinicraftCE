#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "../linked_list.hpp"
#include "tile/tile.hpp"
#include <stdint.h>

// const int MAX_ENTITIES{100};
class Entity;
class Tile;
class Player;

class Level
{
  public:
    // Width and Height in tiles not in pixels.
    int width, height;
    // x_offset and y_offset in world coordinates
    int x_offset, y_offset;
    // array of tile id's
    uint8_t* tiles;
    uint8_t* data;
    int monster_density;
    // List containing all the entities in the level
    Linked_list<Entity>* entities;
    Player* player;

    Level(int width, int height, int level, Level* parent_level);
    ~Level();

    void render_background(int x_scroll, int y_scroll);
    inline Tile* get_tile(int x, int y);
    void set_tile(int x, int y, Tile* t, uint8_t dataval);
    uint8_t get_data(int x, int y);
    void set_data(int x, int y, uint8_t val);
    void add(Entity* entity);
    void remove(Entity* e);
    void try_spawn(int count);
    void tick();
    Linked_list<Entity>* get_entities(int x0, int y0, int x1, int y1);

  private:
    int depth;
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
