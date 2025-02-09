#include "font.hpp"
#include "../gfx/minigfx1.h"
#include <fontlibc.h>
#include <graphx.h>

Font::Font()
{
}

Font::~Font()
{
}

void Font::print_centered(const char* msg)
{
    fontlib_SetCursorPosition(fontlib_GetWindowWidth() / 2 + fontlib_GetWindowXMin() -
                                  (fontlib_GetStringWidth(msg) / 2),
                              fontlib_GetCursorY());
    fontlib_DrawString(msg);
}
// x and in screen pixel coordinates, colors mapped with index in convimg.yaml
void Font::draw(const char* msg, int x, int y, uint8_t fore_color, uint8_t back_color)
{
    if (back_color == 1) // if the background is transparent
    {
        fontlib_SetTransparency(true);
    }
    fontlib_SetWindow(x, y, fontlib_GetStringWidth(msg), 16);
    fontlib_HomeUp();
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    fontlib_SetColors(fore_color, back_color);
    fontlib_DrawString(msg);
    fontlib_SetTransparency(false);
}
// x and y in screen pixel coordinates, colors mapped with index in convimg.yaml
void Font::draw(uint8_t number, uint8_t msg_length, int x, int y, uint8_t fore_color, uint8_t back_color)
{
    if (y < GFX_LCD_HEIGHT - 64)
    {
        if (back_color == 1) // if the background is transparent
        {
            fontlib_SetTransparency(true);
        }
        fontlib_SetWindow(x, y, msg_length * 16, 16);
        fontlib_HomeUp();
        fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
        fontlib_SetColors(fore_color, back_color);
        fontlib_DrawUInt(number, msg_length);
        fontlib_SetTransparency(false);
    }
    else
    {
        return;
    }
}
// x,y,width and height are all in 16 pixel font length
void Font::render_frame(const char* title, uint8_t title_length, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    gfx_RLETSprite_NoClip(rlet_frame_corner, x * 16, y * 16);
    gfx_RLETSprite_NoClip(rlet_frame_corner_flipped_y, x * 16 + (width - 1) * rlet_frame_corner_flipped_y_width,
                          y * 16);
    gfx_RLETSprite_NoClip(rlet_frame_corner_flipped_x, x * 16,
                          y * 16 + (height - 1) * rlet_frame_corner_flipped_x_height);
    gfx_RLETSprite_NoClip(rlet_frame_corner_flipped_xy, x * 16 + (width - 1) * rlet_frame_corner_flipped_xy_width,
                          y * 16 + (height - 1) * rlet_frame_corner_flipped_xy_height);
    for (uint8_t w = 1; w < width - 1; w++)
    {
        gfx_RLETSprite_NoClip(rlet_frame_side, x * 16 + w * rlet_frame_side_width, y * 16);
        gfx_RLETSprite_NoClip(rlet_frame_side_flipped_x, x * 16 + w * rlet_frame_side_flipped_x_width,
                              y * 16 + (height - 1) * rlet_frame_side_flipped_x_height);
    }
    for (uint8_t h = 1; h < height - 1; h++)
    {
        gfx_RLETSprite_NoClip(rlet_frame_side_rotated_270, x * 16, y * 16 + h * rlet_frame_side_rotated_270_height);
        gfx_RLETSprite_NoClip(rlet_frame_side_rotated_90, x * 16 + (width - 1) * rlet_frame_side_rotated_90_width,
                              y * 16 + h * rlet_frame_side_rotated_90_width);
    }
    gfx_SetColor(5);
    gfx_FillRectangle_NoClip(x * 16 + rlet_frame_corner_width, y * 16 + rlet_frame_corner_height,
                             (width - 2) * rlet_frame_corner_width, (height - 2) * rlet_frame_corner_height);

    draw(title, x * 16 + 16, y * 16, 6, 5);
}
