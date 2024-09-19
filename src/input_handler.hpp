#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <keypadc.h>

class Key
{
  public:
    int presses, absorbs; // presses determine how long you held it down, absorbs will determined if you clicked
    bool down, clicked;

    void toggle(bool pressed);
    void tick();
};

class Input_handler
{
  public:
    Key* up;
    Key* down;
    Key* left;
    Key* right;
    Key* attack;
    Key* menu;

    Input_handler();
    void tick();
};

#endif
