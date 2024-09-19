#include "gfx/gfx.h"
#include <graphx.h>
#include <keypadc.h>

int main()
{
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    while (kb_Data[1] != kb_Del)
    {
        gfx_ZeroScreen(); // makes the screen totaly white
        gfx_RLETSprite(player, GFX_LCD_WIDTH / 2, GFX_LCD_HEIGHT / 2);
        gfx_SwapDraw();
    }

    gfx_End();

    return 0;
}
