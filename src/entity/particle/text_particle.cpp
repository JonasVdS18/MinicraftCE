#include "text_particle.hpp"
#include "../../screen/font.hpp"
#include <sys/util.h>
// col = textcolor
Text_particle::Text_particle(char* msg, uint8_t msg_length, int x, int y, uint8_t col)
    : Entity(), msg{msg}, number{0}, msg_length{msg_length}, col{col}, time{0}
{
    this->x = x;
    this->y = y;
    xx = x;
    yy = y;
    zz = 2;
    xa = (float)randInt(0, 2) * 0.3;
    ya = (float)randInt(0, 2) * 0.3;
    za = (float)(randInt(0, 10)) / 10.0 * 0.7 + 2;
}
Text_particle::Text_particle(uint8_t number, uint8_t msg_length, int x, int y, uint8_t col)
    : Entity(), msg{NULL}, number{number}, msg_length{msg_length}, col{col}, time{0}
{
    this->x = x;
    this->y = y;
    xx = x;
    yy = y;
    zz = 2;
    xa = (float)randInt(0, 2) * 0.3;
    ya = (float)randInt(0, 2) * 0.3;
    za = (float)(randInt(0, 10)) / 10.0 * 0.7 + 2;
}
Text_particle::~Text_particle()
{
}

void Text_particle::tick()
{
    Entity::tick();
    time++;
    if (time > 60)
    {
        remove();
    }
    xx += xa;
    yy += ya;
    zz += za;
    if (zz < 0)
    {
        zz = 0;
        za *= -0.5;
        xa *= 0.6;
        ya *= 0.6;
    }
    za -= 0.15;
    x = (int)xx;
    y = (int)yy;
}

void Text_particle::render(int x_scroll, int y_scroll)
{
    if (msg != NULL)
    {
        Font::draw(msg, msg_length, x - x_scroll + 2, y - y_scroll - (int)zz + 2, 0, 1);
        Font::draw(msg, msg_length, x - x_scroll, y - y_scroll - (int)zz, col, 1);
    }
    else
    {
        Font::draw(number, msg_length, x - x_scroll + 2, y - y_scroll - (int)zz + 2, 0, 1);
        Font::draw(number, msg_length, x - x_scroll, y - y_scroll - (int)zz, col, 1);
    }
}
