#include "input_handler.hpp"
#include <keypadc.h>

Key::Key()
{
    this->clicked = false;
    this->down = false;
    this->clickable = true;
}

void Key::toggle(bool pressed)
{
    down = pressed;
}
void Key::tick()
{

    if (down && clicked)
    {
        clicked = false;
    }
    if (down && clickable)
    {
        clicked = true;
        clickable = false;
    }
    if (!down)
    {
        clickable = true;
    }
}

Input_handler::Input_handler()
{
    up = new Key();
    down = new Key();
    left = new Key();
    right = new Key();
    attack = new Key();
    menu = new Key();
    quit = new Key();
}

void Input_handler::tick()
{
    kb_Scan();

    up->toggle(kb_IsDown(kb_KeyUp));
    down->toggle(kb_IsDown(kb_KeyDown));
    left->toggle(kb_IsDown(kb_KeyLeft));
    right->toggle(kb_IsDown(kb_KeyRight));
    attack->toggle(kb_IsDown(kb_Key2nd));
    menu->toggle(kb_IsDown(kb_KeyAlpha));
    quit->toggle(kb_IsDown(kb_KeyDel));

    up->tick();
    down->tick();
    left->tick();
    right->tick();
    attack->tick();
    menu->tick();
    quit->tick();
}
