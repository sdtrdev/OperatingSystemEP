#include <drivers/driver.h>
#include <common/stdlib.h>

struct driver drivers[IDT_SIZE] = { NULL };
static uint16_t driver_number = 0;

void add_driver(uint8_t interrupt_no, struct driver driver) {
    drivers[interrupt_no] = driver;
}

void init_drivers(void) {
    for(int i = 0; i < IDT_SIZE; ++i)
        if(drivers[i].init != NULL)
            drivers[i].init();
}

driver_handler get_handler(uint8_t interrupt_no) {
    return drivers[interrupt_no].handler;
}