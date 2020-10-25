#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <common/stdint.h>
#include <hardware/idt.h>
#include <hardware/port.h>

#define KEYBOARD_INT    0x21

uint32_t keyboard_handler(uint32_t);
void init_keyboard(void);
typedef void (*handle_keyboard)(char);

struct keyboard_event {
    handle_keyboard on_key_down;
    handle_keyboard on_key_up;
};

#endif