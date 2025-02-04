#include "font.hpp"
#include "../gfx/gfx.h"
#include <fontlibc.h>
#include <graphx.h>

Font::Font()
{
}

Font::~Font()
{
}

void Font::draw(const char* msg, uint8_t msg_length, int x, int y) // x and y in screen pixel coordinates
{
    fontlib_SetWindow(x, y, msg_length * 16, 16);
    fontlib_HomeUp();
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    fontlib_SetColors(6, 5);
    fontlib_DrawString(msg);
}

void Font::renderFrame(const char* title, uint8_t title_length, int x, int y, uint8_t width,
                       uint8_t height) // x and y in screen pixels, width and height in 16x16 menu tiles
{
    gfx_RLETSprite_NoClip(rlet_frame_corner, x, y);
    gfx_RLETSprite_NoClip(rlet_frame_corner_flipped_y, x + (width - 1) * rlet_frame_corner_flipped_y_width, y);
    gfx_RLETSprite_NoClip(rlet_frame_corner_flipped_x, x, y + (height - 1) * rlet_frame_corner_flipped_x_height);
    gfx_RLETSprite_NoClip(rlet_frame_corner_flipped_xy, x + (width - 1) * rlet_frame_corner_flipped_xy_width,
                          y + (height - 1) * rlet_frame_corner_flipped_xy_height);
    for (uint8_t w = 1; w < width - 1; w++)
    {
        gfx_RLETSprite_NoClip(rlet_frame_side, x + w * rlet_frame_side_width, y);
        gfx_RLETSprite_NoClip(rlet_frame_side_flipped_x, x + w * rlet_frame_side_flipped_x_width,
                              y + (height - 1) * rlet_frame_side_flipped_x_height);
    }
    for (uint8_t h = 1; h < height - 1; h++)
    {
        gfx_RLETSprite_NoClip(rlet_frame_side_rotated_270, x, y + h * rlet_frame_side_rotated_270_height);
        gfx_RLETSprite_NoClip(rlet_frame_side_rotated_90, x + (width - 1) * rlet_frame_side_rotated_90_width,
                              y + h * rlet_frame_side_rotated_90_width);
    }
    gfx_SetColor(5);
    gfx_FillRectangle_NoClip(x + rlet_frame_corner_width, y + rlet_frame_corner_height,
                             (width - 2) * rlet_frame_corner_width, (height - 2) * rlet_frame_corner_height);

    draw(title, title_length, x + 16, y);
}
