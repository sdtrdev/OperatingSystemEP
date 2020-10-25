#include <drivers/video.h>
#include <common/stdint.h>
#include <hardware/port.h>

static void get_keycode(char keycode);

static uint16_t *vidptr = (uint16_t *)0xb8000;

static uint16_t get_cursor_offset(void)
{
    uint16_t cursor_offset = 0x00;
    write_port_8bit(REG_SCREEN_CMD, GET_HIGHER_OFFSET);
    cursor_offset = read_port_8bit(REG_SCREEN_DATA) << 8;
    write_port_8bit(REG_SCREEN_CMD, GET_LOWER_OFFSET);
    cursor_offset += read_port_8bit(REG_SCREEN_DATA);
    return cursor_offset;
}

static void set_cursor_offset(uint16_t offset)
{
    write_port_8bit(REG_SCREEN_CMD, GET_HIGHER_OFFSET);
    write_port_8bit(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
    write_port_8bit(REG_SCREEN_CMD, GET_LOWER_OFFSET);
    write_port_8bit(REG_SCREEN_DATA, (uint8_t)(offset & 0xFF));
}

void print_hex(uint8_t number)
{
    char test[] = "00";
    char *hex = "0123456789ABCDEF";
    test[0] = hex[(number >> 4) & 0x0F];
    test[1] = hex[number & 0x0F];
    for (uint16_t i = 0; test[i] != '\0'; i++)
        put_character(test[i]);
}

void print_hex_32(uint32_t number) {
    print_hex((number >> 24) & 0xFF);
    print_hex((number >> 16) & 0xFF);
    print_hex((number >> 8) & 0xFF);
    print_hex(number & 0xFF);
}

void clear_screen()
{
    unsigned int j = 0;
    set_cursor_offset(0);
    while (j < 80 * 25 * 2)
    {
        uint16_t temp = 0x07 << 8;
        temp += ' ';
        vidptr[j] = temp;
        ++j;
    }
}

void kprint(const char *str)
{
    for (unsigned int j = 0;str[j] != '\0'; ++j)
    {
        put_character(str[j]);
    }
}

void put_character(char character)
{
    uint16_t cursor = get_cursor_offset();
    uint16_t vid_char = 0x07 << 8;
    vid_char += character; // BLACK - WHITE
    vidptr[cursor] = vid_char;
    set_cursor_offset(cursor + 1);
}

static void get_keycode(char keycode)
{
    char str[10];
    int i = 0;
    while (keycode)
    {
        str[i++] = '0' + (keycode % 10);
        keycode /= 10;
    }

    while (i > -1)
    {
        vidptr[get_cursor_offset()] = str[--i];
    }
}