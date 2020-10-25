#ifndef __DRIVER_H
#define __DRIVER_H

#include <common/stdint.h>
#include <hardware/idt.h>

typedef uint32_t (*driver_handler)(uint32_t);
typedef void (*init_driver)(void);

struct driver
{
    init_driver init;
    driver_handler handler;
};

extern struct driver drivers[IDT_SIZE];

int32_t reset();
void add_driver(uint8_t interrupt_no, struct driver driver);
void init_drivers(void);
driver_handler get_handler(uint8_t interrupt_no);

#endif