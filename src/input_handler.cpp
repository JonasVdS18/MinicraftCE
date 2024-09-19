#include "input_handler.hpp"

void Key::toggle(bool pressed)
{
    if (pressed != down)
    {
        down = pressed; // If the key is being pressed, then down is true.
    }
    if (pressed)
    {
        presses++;
    }
}
void Key::tick()
{
    if (absorbs < presses)
    {
        absorbs++;
        clicked = true;
    }
    else
    {
        clicked = false;
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
}

void Input_handler::tick()
{
    kb_Scan();

    up->toggle(kb_IsDown(kb_KeyUp));
    down->toggle(kb_IsDown(kb_KeyDown));
    left->toggle(kb_IsDown(kb_KeyLeft));
    right->toggle(kb_IsDown(kb_KeyRight));
    attack->toggle(kb_IsDown(kb_Key2nd));
    up->toggle(kb_IsDown(kb_KeyAlpha));

    up->tick();
    down->tick();
    left->tick();
    right->tick();
    attack->tick();
    menu->tick();
}
