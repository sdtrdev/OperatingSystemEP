#include <drivers/mouse.h>
#include <task/task.h>

#define MOUSE_CMD 0x64
#define MOUSE_DATA 0x60

void put_character(char);

#define LEFT_SHIFT_P 0x2A
#define LEFT_SHIFT_R 0xAA

#define RIGHT_SHIFT_P 0x36
#define RIGHT_SHIFT_R 0xB6

uint8_t buffer[3];
uint8_t offset;
uint8_t buttons;

void init_mouse(void)
{
    offset = 2;
    buttons = 0;
    uint8_t status;
    if (get_focused_task() != NULL && get_focused_task()->mouse != NULL && get_focused_task()->mouse->on_mouse_init != NULL)
        get_focused_task()->mouse->on_mouse_init();

    write_port_8bit(MOUSE_CMD, 0xA8);
    write_port_8bit(MOUSE_CMD, 0x20);
    status = read_port_8bit(MOUSE_DATA) | 2;
    write_port_8bit(MOUSE_CMD, 0x60);
    write_port_8bit(MOUSE_DATA, status);

    write_port_8bit(MOUSE_CMD, 0xD4);
    write_port_8bit(MOUSE_DATA, 0xF4);
    read_port_8bit(MOUSE_DATA);
}

uint32_t mouse_handler(uint32_t esp)
{
    uint8_t status = read_port_8bit(MOUSE_CMD);
    //static int8_t x = 40, y = 12;
    if (!(status & 0x20))
        return esp;

    buffer[offset] = read_port_8bit(MOUSE_DATA);

    if (get_focused_task() == NULL || get_focused_task()->mouse == NULL)
        return esp;

    offset = (offset + 1) % 3;

    if (offset == 0)
    {
        if (buffer[1] != 0 || buffer[2] != 0)
        {
            if(get_focused_task()->mouse->on_mouse_move != NULL)
                get_focused_task()->mouse->on_mouse_move((int8_t)buffer[1], -(int8_t)buffer[2]);
        }
        for (uint8_t i = 0; i < 3; ++i)
        {
            if ((buffer[0] & (0x01 << i)) != (buttons & (0x01 << i)))
            {
                if (buttons & (1 << i) && get_focused_task()->mouse->on_mouse_up != NULL)
                    get_focused_task()->mouse->on_mouse_up(i + 1);
                else if(get_focused_task()->mouse->on_mouse_down != NULL)
                    get_focused_task()->mouse->on_mouse_down(i + 1);
            }
        }
        buttons = buffer[0];
    }

    return esp;
}