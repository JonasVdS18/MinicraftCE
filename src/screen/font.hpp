#ifndef FONT_HPP
#define FONT_HPP
#include <stdint.h>
class Font
{
  public:
    Font();
    ~Font();
    static void draw(const char* msg, uint8_t msg_length, int x, int y); // x and y in screen pixel coordinates
    static void renderFrame(const char* title, uint8_t title_length, int x, int y, uint8_t width,
                            uint8_t height); // x and y in screen pixels, width and height in 16x16 menu tiles
    static void print_centered(const char* string);
};

#endif
