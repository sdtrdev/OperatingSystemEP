#ifndef __MOUSE_H
#define __MOUSE_H

#include <common/stdint.h>
#include <hardware/idt.h>
#include <hardware/port.h>

#define MOUSE_INT    0x2C

typedef void (*mouse_button_handler)(uint8_t button);
typedef void (*mouse_move_handler)(int32_t offset_x,int32_t offset_y);
typedef void (*mouse_init_handler)(void);

struct mouse_event {
    mouse_button_handler on_mouse_down;
    mouse_button_handler on_mouse_up;
    mouse_move_handler on_mouse_move;
    mouse_init_handler on_mouse_init;
};

uint32_t mouse_handler(uint32_t);
void init_mouse(void);

#endif