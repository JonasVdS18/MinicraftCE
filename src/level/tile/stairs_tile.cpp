#include "stairs_tile.hpp"

Stairs_tile::Stairs_tile(uint8_t id, bool leads_up) : Tile(id), leads_up{leads_up}
{
}

Stairs_tile::~Stairs_tile()
{
}
