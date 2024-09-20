#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

class Key
{
  private:
    bool clickable;

  public:
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
