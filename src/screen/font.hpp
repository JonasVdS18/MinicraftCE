#ifndef FONT_HPP
#define FONT_HPP
#include <stdint.h>
class Font
{
  public:
    Font();
    ~Font();
    // x and y in screen pixel coordinates, colors mapped with index in convimg.yaml
    static void draw(const char* msg, int x, int y, uint8_t fore_color, uint8_t back_color);
    // x and y in screen pixel coordinates, colors mapped with index in convimg.yaml
    static void draw(uint8_t number, uint8_t msg_length, int x, int y, uint8_t fore_color, uint8_t back_color);
    static void render_frame(const char* title, uint8_t title_length, uint8_t x, uint8_t y, uint8_t width,
                             uint8_t height); // x and y in screen pixels, width and height in 16x16 menu tiles
    static void print_centered(const char* string);
};

#endif
