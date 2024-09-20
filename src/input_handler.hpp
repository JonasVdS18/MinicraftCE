#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

class Key
{
  public:
    int presses, absorbs; // presses determine how long you held it down, absorbs will determined if you clicked
    bool down, clicked;
    Key();
    ~Key() = default;

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
    Key* quit;

    Input_handler();
    ~Input_handler() = default;
    void tick();
};

#endif
