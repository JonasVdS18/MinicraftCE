#include "input_handler.hpp"
#include <keypadc.h>

Key::Key() : clickable{true}, down{false}, clicked{false}
{
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
    : up{new Key()}, down{new Key()}, left{new Key()}, right{new Key()}, attack{new Key()}, menu{new Key()},
      quit{new Key()}
{
}

Input_handler::~Input_handler()
{
    delete up;
    delete down;
    delete left;
    delete right;
    delete attack;
    delete menu;
    delete quit;
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
