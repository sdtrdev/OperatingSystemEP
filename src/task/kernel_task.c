#include <task/kernel_task.h>
#include <drivers/video.h>

static int32_t x = 0; 
static int32_t y = 0;
static uint16_t *vidptr = (uint16_t *)0xb8000;


void on_key_down(char character)
{
    put_character(character);
}
void on_key_up(char character)
{
}

void on_mouse_move(int32_t offset_x,int32_t offset_y)
{
    vidptr[80 * y + x] = ((vidptr[80 * y + x] & 0xF000) >> 4) | ((vidptr[80 * y + x] & 0x0F00) << 4) | (vidptr[80 * y + x] & 0x00FF);
    x += offset_x;
    if (x < 0)
        x = 0;
    if (x >= 80)
        x = 79;

    y += offset_y;
    if (y < 0)
        y = 0;
    if (y >= 25)
        y = 24;
    vidptr[80 * y + x] = ((vidptr[80 * y + x] & 0xF000) >> 4) | ((vidptr[80 * y + x] & 0x0F00) << 4) | (vidptr[80 * y + x] & 0x00FF);
}
void on_mouse_down(uint8_t button)
{
    vidptr[80 * y + x] = ((vidptr[80 * y + x] & 0xF000) >> 4) | ((vidptr[80 * y + x] & 0x0F00) << 4) | (vidptr[80 * y + x] & 0x00FF);
}
void on_mouse_up(uint8_t button)
{
    vidptr[80 * y + x] = ((vidptr[80 * y + x] & 0xF000) >> 4) | ((vidptr[80 * y + x] & 0x0F00) << 4) | (vidptr[80 * y + x] & 0x00FF);
}

void on_mouse_init(void) {
    y = 12;
    x = 40;
    vidptr[80 * y + x] = ((vidptr[80 * y + x] & 0xF000) >> 4) | ((vidptr[80 * y + x] & 0x0F00) << 4) | (vidptr[80 * y + x] & 0x00FF);
}