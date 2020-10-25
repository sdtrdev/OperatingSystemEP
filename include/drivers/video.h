#ifndef __VIDEO_H
#define __VIDEO_H

#include <common/stdint.h>

#define REG_SCREEN_CMD      0x3d4
#define REG_SCREEN_DATA     0x3d5

#define GET_HIGHER_OFFSET   0xE
#define GET_LOWER_OFFSET    0xF

void clear_screen(void);

void kprint(const char *str);

void put_character(char character);

void print_hex(uint8_t number);
void print_hex_32(uint32_t number);

#endif