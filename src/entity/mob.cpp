#include "mob.hpp"
#include "../entity/player.hpp"
#include "../level/level.hpp"
#include "../level/tile/tile.hpp"
#include <sys/util.h>

class Level;

Mob::Mob()
    : Mob::Entity(), walk_dist{0}, dir{0}, x_knockback{0}, y_knockback{0}, hurt_time{0}, maxhealth{10},
      health{maxhealth}, swim_timer{0}, tick_time{0}
{
    x = 8;
    y = 8;
    radius_x = 4;
    radius_y = 3;
}

Mob::~Mob()
{
}

void Mob::tick()
{
    tick_time++;
    if (level->get_tile(x >> 5, y >> 5) == Tile::lava) // >> 5 = divides by 32
    {
        hurt(this, 4, dir ^ 1);
    }
    if (health <= 0)
    {
        die();
    }
    if (hurt_time > 0)
    {
        hurt_time--;
    }
}

void Mob::die()
{
    remove();
}

bool Mob::move(int xa, int ya)
{
    if (is_swimming())
    {
        swim_timer++;
        if ((swim_timer % 2) == 0) // halves the swim speed by only moving half the time
        {
            return true;
        }
    }
    if (x_knockback < 0)
    {
        move2(-1, 0);
        x_knockback++; // increases so it reaches 0 and the mob will not be knocked back any further;
    }
    if (x_knockback > 0)
    {
        move2(1, 0);
        x_knockback--;
    }
    if (y_knockback < 0)
    {
        move2(0, -1);
        y_knockback++;
    }
    if (x_knockback > 0)
    {
        move2(0, 1);
        y_knockback--;
    }

    if (hurt_time > 0) // If we have been hurt recently and haven't yet cooled down, don't continue with the movement
                       // (so only knockback will be performed)
    {
        return true;
    }

    if (xa != 0 || ya != 0) // Only if horizontal or vertical movement is actually happening
    {
        walk_dist++;
        if (xa < 0)
            dir = 2; // Set the mob's direction based on movement: left
        if (xa > 0)
            dir = 3; // right
        if (ya < 0)
            dir = 1; // up
        if (ya > 0)
            dir = 0; // down
    }

    return Entity::move(xa, ya);
}

bool Mob::is_swimming()
{
    Tile* tile = level->get_tile(x >> 5, y >> 5);
    return (tile == Tile::water || tile == Tile::lava);
}

bool Mob::blocks(Entity* entity)
{
    return entity->is_blockable_by(this);
}

void Mob::hurt(Mob* mob, int damage, int attack_dir)
{
    do_hurt(damage, attack_dir);
}

void Mob::hurt(Tile* tile, int x, int y, int damage)
{
    uint8_t attack_dir =
        dir ^ 1; // Set attackDir to our own direction, inverted. XORing it with 1 flips the rightmost bit in the
                 // variable, this effectively adds one when even, and subtracts one when odd
    do_hurt(damage, attack_dir);
}

void Mob::heal(uint8_t heal)
{
    if (hurt_time > 0)
    {
        return;
    }

    //!!!!!!!!!! level->add(new Text_particle("" + heal, x, y, green));

    health += heal;
    if (health > maxhealth)
    {
        health = maxhealth;
    }
}

void Mob::do_hurt(uint8_t damage, uint8_t attack_dir)
{
    if (hurt_time > 0)
    {
        return;
    }

    //!!!!!!!!!! level->add(new TextParticle("" + damage, x, y, red));

    health -= damage;
    if (attack_dir == 0)
        y_knockback = 6; // If the direction is downwards, add positive vertical knockback
    if (attack_dir == 1)
        y_knockback = -6; // If the direction is upwards, add negative vertical knockback
    if (attack_dir == 2)
        x_knockback = -6; // If the direction is to the left, add negative horizontal knockback
    if (attack_dir == 3)
        x_knockback = 6; // If the direction is to the right, add positive horizontal knockback
    hurt_time = 10;      // Set a delay before we can be hurt again
}

bool Mob::find_start_pos(Level* level)
{
    int x = randInt(0, level->width - 1);
    int y = randInt(0, level->height - 1);
    int xx = x * 32 + 16; // Get actual pixel coordinates from this tile coord
    int yy = y * 32 + 16;

    if (level->player != NULL)
    {
        int xd = level->player->x - xx; // Get the difference between our attempted spawn x, and the player's x
        int yd = level->player->y - yy; // Get the difference between our attempted spawn y, and the player's y
        if (xd * xd + yd * yd < 80 * 80)
            return false; // Use pythagoras' theorem to determine the distance between us and the player, and if it is
                          // less than 80 (too close) then return false
    }

    int r = level->monster_density *
            32; // Get the allowed density of mobs in the level, convert it from a tile to a real coordinate

    Linked_list<Entity>* entities_around_player{level->get_entities(xx - r, yy - r, xx + r, yy + r)};
    if (entities_around_player->size() > 0)
    {
        delete entities_around_player;
        return false; // Get a list of mobs in the level, within a box centered on our attempted coordinates, with
                      // dimensions of r times 2, and if there are any close to us, return false;
    }

    delete entities_around_player;

    if (level->get_tile(x, y)->may_pass(level, x, y, this))
    { // Check if the tile we're trying to spawn on is not solid to us
        this->x = xx;
        this->y = yy;
        return true;
    }

    return false;
}
