#include "player.hpp"
// #include "../level/level.hpp"
#include "../gfx/minigfx1.h"
#include "../level/tile/tile.hpp"
#include "../screen/inventory_menu.hpp"
// #include <debug.h>
#include <debug.h>
#include <sys/util.h>

Player::Player(Game* game, Input_handler* input)
    : Mob(), attack_time{0}, attack_dir{dir}, on_stair_delay{0}, game{game}, input{input}, inventory(new Inventory()),
      active_item{NULL}, attack_item{active_item}, max_stamina{10}, stamina{max_stamina}, stamina_recharge(0),
      stamina_recharge_delay{0}, invulnerable_time{0}

{
    x = 10 * 32;
    y = 10 * 32;
    // inventory->add(new FurnitureItem(new Workbench()));
    // inventory->add(new PowerGloveItem());
}

Player::~Player()
{
    if (active_item == attack_item)
    {
        delete active_item;
    }
    if (active_item != NULL)
    {
        delete active_item;
    }
    if (attack_item != NULL)
    {
        delete attack_item;
    }
    delete inventory;
}

void Player::tick()
{
    Mob::tick();

    if (invulnerable_time > 0)
    {
        invulnerable_time--;
    }
    Tile* on_tile = level->get_tile(x >> 5, y >> 5); // gets the current tile the player is on.
    if (on_tile == Tile::stairs_down || on_tile == Tile::stairs_up)
    {
        if (on_stair_delay == 0)
        {
            change_level((on_tile == Tile::stairs_up)
                             ? 1
                             : -1); // if the statementi s true inout 1 in change_level, if false, input -1
            on_stair_delay = 10;
            return;
        }
        on_stair_delay = 10;
    }
    else
    {
        if (on_stair_delay > 0)
        {
            on_stair_delay--;
        }
    }

    if (stamina <= 0 && stamina_recharge_delay == 0 && stamina_recharge == 0)
    {
        stamina_recharge_delay = 40;
    }

    if (stamina_recharge_delay > 0)
    {
        stamina_recharge_delay--;
    }

    if (stamina_recharge_delay == 0)
    {
        stamina_recharge++;
        if (is_swimming())
        {
            stamina_recharge = 0;
        }
        while (stamina_recharge > 10)
        {
            stamina_recharge -= 10;
            if (stamina < max_stamina)
            {
                stamina++;
            }
        }
    }

    int8_t xa = 0; // x acceleration
    int8_t ya = 0; // y acceleration
    if (input->up->down && level->y_offset > 0)
    {
        ya--;
    }
    if (input->down->down && level->y_offset + TILE_DRAW_HEIGHT * TILE_HEIGHT < level->height * 32)
    {
        ya++;
    }
    if (input->left->down && level->x_offset > 0)
    {
        xa--;
    }
    if (input->right->down && level->x_offset + TILE_DRAW_WIDTH * TILE_WIDTH < level->width * 32)
    {
        xa++;
    }

    if (is_swimming() && (tick_time % 60) == 0)
    {
        if (stamina > 0)
        {
            stamina--;
        }
        else
        {
            Mob::hurt(this, 1, dir ^ 1);
        }
    }

    if (stamina_recharge_delay % 2 == 0)
    {
        move(xa, ya);
    }

    if (input->attack->clicked)
    {
        if (stamina > 0)
        {
            stamina--;
            stamina_recharge = 0;
            attack();
        }
    }

    if (input->menu->clicked)
    {
        // dbg_printf("CLICKED INVENTORY\n");
        if (!use())
        {
            // dbg_printf("NOT USE\n");
            game->set_menu(new Inventory_menu(this));
        }
    }

    if (attack_time > 0)
    {
        attack_time--;
    }
}

void Player::change_level(int8_t dir)
{
    game->schedule_level_change(dir);
}

bool Player::use()
{
    if (dir == 0 && use(x - 8, y + 4 - 2, x + 8, y + 12 - 2))
    {
        return true; // if the entity below has a use() method then return true
    }
    if (dir == 1 && use(x - 8, y - 12 - 2, x + 8, y - 4 - 2))
    {
        return true; // if the entity above has a use() method then return true
    }
    if (dir == 3 && use(x + 4, y - 8 - 2, x + 12, y + 8 - 2))
    {
        return true; // if the entity to the right has a use() method then return true
    }
    if (dir == 2 && use(x - 12, y - 8 - 2, x - 4, y + 8 - 2))
    {
        return true; // if the entity to the left has a use() method then return true
    }
    return false;
}

bool Player::use(int x0, int y0, int x1, int y1)
{
    Linked_list<Entity>* entities = level->get_entities(x0, y0, x1, y1);
    int entities_size{entities->size()};
    for (int i = 0; i < entities_size; i++)
    {
        Entity* entity = entities->get(i);
        if (entity != this)
        {
            if (entity->use(this, attack_dir))
            {
                delete entities;
                return true;
            }
        }
    }
    delete entities;
    return false;
}

bool Player::interact(int x0, int y0, int x1, int y1)
{
    Linked_list<Entity>* entities = level->get_entities(x0, y0, x1, y1);
    int entities_size{entities->size()};
    for (int i = 0; i < entities_size; i++)
    {
        Entity* entity = entities->get(i);
        if (entity != this && entity->interact(this, active_item, attack_dir))
        {
            delete entities;
            return true;
        }
    }
    delete entities;
    return false;
}

void Player::attack()
{
    walk_dist += 8; // increase the walkDist (changes the sprite)
    attack_dir = dir;
    attack_item = active_item;
    bool done = false;
    int8_t y_offset = -2;
    uint8_t range = 12;
    int x_tile = x >> 5;
    int y_tile = (y + y_offset) >> 5;
    uint8_t r = 12;

    if (active_item != NULL)
    {
        attack_time = 10;
        if (dir == 0 && interact(x - 8, y + 4 + y_offset, x + 8, y + range + y_offset))
        {
            done = true;
        }
        if (dir == 1 && interact(x - 8, y - range + y_offset, x + 8, y - 4 + y_offset))
        {
            done = true;
        }
        if (dir == 3 && interact(x + 4, y - 8 + y_offset, x + range, y + 8 + y_offset))
        {
            done = true;
        }
        if (dir == 2 && interact(x - range, y - 8 + y_offset, x - 4, y + 8 + y_offset))
        {
            done = true;
        }
        if (done)
        {
            return;
        }

        if (attack_dir == 0)
        {
            y_tile = (y + r + y_offset) >> 4; // gets the tile below that you are attacking.
        }
        if (attack_dir == 1)
        {
            y_tile = (y - r + y_offset) >> 4; // gets the tile above that you are attacking.
        }
        if (attack_dir == 2)
        {
            x_tile = (x - r) >> 4; // gets the tile to the left that you are attacking.
        }
        if (attack_dir == 3)
        {
            x_tile = (x + r) >> 4; // gets the tile to the right that you are attacking.
        }

        if ((x_tile >= 0) && (y_tile >= 0) && (x_tile < level->width) && (y_tile < level->height))
        {
            if (active_item->interact_on(level->get_tile(x_tile, y_tile), level, x_tile, y_tile, this, attack_dir))
            {
                done = true;
            }
            else
            {
                if (level->get_tile(x_tile, y_tile)->interact(level, x_tile, y_tile, this, active_item, attack_dir))
                {
                    done = true;
                }
            }
            if (active_item->is_depleted())
            {
                delete active_item;
                active_item = NULL;
            }
        }
    }

    if (done)
    {
        return;
    }

    if (active_item == NULL || active_item->can_attack())
    {
        attack_time = 5;
        range = 20;
        if (dir == 0)
        {
            hurt(x - 8, y + 4 + y_offset, x + 8, y + range + y_offset); // attacks the entity below you.
        }
        if (dir == 1)
        {
            hurt(x - 8, y - range + y_offset, x + 8, y - 4 + y_offset); // attacks the entity above you.
        }
        if (dir == 3)
        {
            hurt(x + 4, y - 8 + y_offset, x + range, y + 8 + y_offset); // attacks the entity to the right of you.
        }
        if (dir == 2)
        {
            hurt(x - range, y - 8 + y_offset, x - 4, y + 8 + y_offset); // attacks the entity to the left of you.
        }
        if (attack_dir == 0)
        {
            y_tile = (y + r + y_offset) >> 4; // gets the tile below that you are attacking.
        }
        if (attack_dir == 1)
        {
            y_tile = (y - r + y_offset) >> 4; // gets the tile above that you are attacking.
        }
        if (attack_dir == 2)
        {
            x_tile = (x - r) >> 4; // gets the tile to the left that you are attacking.
        }
        if (attack_dir == 3)
        {
            x_tile = (x + r) >> 4; // gets the tile to the right that you are attacking.
        }

        if (x_tile >= 0 && y_tile >= 0 && x_tile < level->width && y_tile < level->height)
        {
            level->get_tile(x_tile, y_tile)->hurt(level, x_tile, y_tile, this, randInt(0, 3) + 1, attack_dir);
        }
    }
}

void Player::hurt(int x0, int y0, int x1, int y1)
{
    Linked_list<Entity>* entities = level->get_entities(x0, y0, x1, y1);
    int entities_size{entities->size()};
    for (int i = 0; i < entities_size; i++)
    {
        Entity* entity = entities->get(i);
        if (entity != this)
        {
            entity->hurt(this, get_attack_damage(entity), attack_dir);
        }
    }
    delete entities;
}

uint8_t Player::get_attack_damage(Entity* entity)
{
    uint8_t damage = randInt(0, 3) + 1;
    if (attack_item != NULL)
    {
        damage += attack_item->get_attack_damage_bonus(entity);
    }
    return damage;
}

void Player::render(int x_scroll, int y_scroll)
{
    bool flip = false;
    if ((walk_dist % 32) < 16)
    {
        flip = false;
    }
    else
    {
        flip = true;
    }

    const gfx_rletsprite_t* display_sprite;

    if (dir == 0) // if the direction is 0 (Down)...
    {
        if (!flip)
        {
            display_sprite = rlet_player_front;
        }
        else
        {
            display_sprite = rlet_player_front_flipped_y;
        }
    }
    if (dir == 1) // if the direction is 1 (Up)...
    {
        if (!flip)
        {
            display_sprite = rlet_player_back;
        }
        else
        {
            display_sprite = rlet_player_back_flipped_y;
        }
    }
    if (dir == 2) // if the direction is 2 (Left)...
    {
        if (!flip)
        {
            display_sprite = rlet_player_side_0_flipped_y;
        }
        else
        {
            display_sprite = rlet_player_side_1_flipped_y;
        }
    }
    if (dir == 3) // if the direction is 3 (Right)...
    {
        if (!flip)
        {
            display_sprite = rlet_player_side_0;
        }
        else
        {
            display_sprite = rlet_player_side_1;
        }
    }
    // gfx_RLETSprite_NoClip(display_sprite, (GFX_LCD_WIDTH - rlet_player_front_width) / 2,
    //(GFX_LCD_HEIGHT - rlet_player_front_height) / 2);
    gfx_RLETSprite_NoClip(display_sprite, x - x_scroll, y - y_scroll);
}

void Player::touch_item(Item_entity* item_entity)
{
}

bool Player::can_swim()
{
    return true;
}

bool Player::find_start_pos(Level* level)
{
    while (true)
    {
        // level->width -1 instead of level-width, because randInt is inclusive
        int x = randInt(5, level->width - 5);
        int y = randInt(4, level->height - 4);
        /*
        if (level->get_tile(x, y) == Tile::grass)
        {                        // if the tile at the x & y coordinates is a grass tile then...
            this.x = x * 16 + 8; // the player's x coordinate will be in the middle of the tile
            this.y = y * 16 + 8; // the player's y coordinate will be in the middle of the tile
            return true;         // returns and stop's the loop
        }*/
        // this->x = x * 32 - 16;
        // this->y = y * 32 - 16;

        // +16 to spawn in the center of the tile
        this->x = x * 32 + 16;
        this->y = y * 32 + 16;
        return true;
    }
}

bool Player::pay_stamina(uint8_t cost)
{
    if (cost > stamina)
    {
        return false;
    }
    else
    {
        stamina -= cost;
        return true;
    }
}

uint8_t Player::get_light_radius()
{
    uint8_t r = 2;
    return r;
}

void Player::die()
{
    Mob::die();
}

void Player::touched_by(Entity* entity)
{
    if (!(dynamic_cast<Player*>(entity) == NULL))
    {
        entity->touched_by(this);
    }
}

void Player::do_hurt(uint8_t damage, uint8_t attack_dir)
{
    if (hurt_time > 0 || invulnerable_time > 0)
    {
        return;
    }

    // level->add(new TextParticle("" + damage, x, y, Color.get(-1, 504, 504, 504))); // adds a text particle telling
    // how much damage was done.

    health -= damage;
    if (attack_dir == 0)
    {
        y_knockback = +6; // if the direction was from below, then get knocked above.
    }
    if (attack_dir == 1)
    {
        y_knockback = -6; // if the direction was from above, then get knocked below.
    }
    if (attack_dir == 2)
    {
        x_knockback = -6; // if the direction was from the right, then get knocked to the left.
    }
    if (attack_dir == 3)
    {
        x_knockback = +6; // if the direction was from the left, then get knocked to the right.
    }
    hurt_time = 10; // hurt time set to 10
    invulnerable_time = 30;
}

void Player::game_won()
{
    invulnerable_time = 255;
    game->won();
}
