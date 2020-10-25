#ifndef __PORT_H
#define __PORT_H

#include <common/stdint.h>

#define PIC_MASTER_COMMAND      0x20
#define PIC_MASTER_DATA         0x21

#define PIC_SLAVE_COMMAND      0xA0
#define PIC_SLAVE_DATA         0xA1


void write_port_8bit(uint16_t port, uint8_t data);
void write_port_8bit_slow(uint16_t port, uint8_t data);
void write_port_16bit(uint16_t port, uint16_t data);
void write_port_32bit(uint16_t port, uint32_t data);

uint8_t read_port_8bit(uint16_t port);
uint16_t read_port_16bit(uint16_t port);
uint32_t read_port_32bit(uint32_t port);

#endif
