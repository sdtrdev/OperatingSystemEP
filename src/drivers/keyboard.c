#include <drivers/keyboard.h>
#include <task/kernel_task.h>

#define KEYBOARD_CMD 0x64
#define KEYBOARD_DATA 0x60

void put_character(char);

#define LEFT_SHIFT_P 0x2A
#define LEFT_SHIFT_R 0xAA
#define RIGHT_SHIFT_P 0x36
#define RIGHT_SHIFT_R 0xB6
#define ENTER_KEYCODE       0x1C
#define BACKSPACE_KEYCODE   0x0E
#define ESC_KEYCODE         0x01
#define CAPS_LOCK_KEYCODE   0x3A

int left_shift_pressed = 0;
int right_shift_pressed = 0;
int caps_lock = 0;

void init_keyboard(void)
{
    uint8_t status;

    while (read_port_8bit(KEYBOARD_CMD) & 0x01)
        read_port_8bit(KEYBOARD_DATA);

    write_port_8bit(KEYBOARD_CMD, 0xAE);
    write_port_8bit(KEYBOARD_CMD, 0x20);
    status = (read_port_8bit(KEYBOARD_DATA) | 1) & ~0x10;
    write_port_8bit(KEYBOARD_CMD, 0x60);
    write_port_8bit(KEYBOARD_DATA, status);
    write_port_8bit(KEYBOARD_DATA, 0xF4);
}

/*
    keyboard_handler is main interrupt handler for keyboard
    init_keyboard should have called first at the second
    keyboard_handler should have been setted on interrupt
    descriptor table at 0x21 (33) index!
*/

uint32_t keyboard_handler(uint32_t esp)
{
    uint8_t key = read_port_8bit(0x60);
    if(get_focused_task() == NULL)
        return esp;
    struct keyboard_event* focused_task = get_focused_task()->keyboard;
    if(focused_task == NULL || focused_task->on_key_down == NULL)
        return esp;
    switch (key)
    {
    case 0x02:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? '!' : '1');
        break;
    case 0x03:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? '\'' : '2');
        break;
    case 0x04:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? '^' : '3');
        break;
    case 0x05:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? '+' : '4');
        break;
    case 0x06:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? '%' : '5');
        break;
    case 0x07:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? '&' : '6');
        break;
    case 0x08:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? '/' : '7');
        break;
    case 0x09:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? '(' : '8');
        break;
    case 0x0A:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? ')' : '9');
        break;
    case 0x0B:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? '=' : '0');
        break;
    case 0x10:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'Q' : 'q');
        break;
    case 0x11:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'W' : 'w');
        break;
    case 0x12:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'E' : 'e');
        break;
    case 0x13:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'R' : 'r');
        break;
    case 0x14:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'T' : 't');
        break;
    case 0x15:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'Y' : 'y');
        break;
    case 0x16:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'U' : 'u');
        break;
    case 0x17:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'I' : 'i');
        break;
    case 0x18:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'O' : 'o');
        break;
    case 0x19:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'P' : 'p');
        break;

    case 0x1E:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'A' : 'a');
        break;
    case 0x1F:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'S' : 's');
        break;
    case 0x20:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'D' : 'd');
        break;
    case 0x21:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'F' : 'f');
        break;
    case 0x22:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'G' : 'g');
        break;
    case 0x23:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'H' : 'h');
        break;
    case 0x24:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'J' : 'j');
        break;
    case 0x25:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'K' : 'k');
        break;
    case 0x26:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'L' : 'l');
        break;
    case 0x2C:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'Z' : 'z');
        break;
    case 0x2D:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'X' : 'x');
        break;
    case 0x2E:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'C' : 'c');
        break;
    case 0x2F:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'V' : 'v');
        break;
    case 0x30:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'B' : 'b');
        break;
    case 0x31:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'N' : 'n');
        break;
    case 0x32:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed || caps_lock ? 'M' : 'm');
        break;
    case 0x33:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? ';' : ',');
        break;
    case 0x34:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? ':' : '.');
        break;
    case 0x35:
        focused_task->on_key_down(left_shift_pressed || right_shift_pressed ? '_' : '-');
        break;
    case 0x1C:
        focused_task->on_key_down('\n');
        break;
    case 0x39:
        focused_task->on_key_down(' ');
        break;
    case 0x9E:
        break; //RELEASE A
    case LEFT_SHIFT_P:
        left_shift_pressed = 1;
        break;
    case LEFT_SHIFT_R:
        left_shift_pressed = 0;
        break;
    case RIGHT_SHIFT_P:
        right_shift_pressed = 1;
        break;
    case RIGHT_SHIFT_R:
        right_shift_pressed = 0;
        break;
    case CAPS_LOCK_KEYCODE:
        caps_lock = !caps_lock;
        break;
    case 0xFA:
    case 0x61:
        break;
    case 0x45: //NumLock
    case 0xC5:
        break;
    default:
        if (key < 0x80)
        {
            char test[] = "KEYBOARD 0x00 ";
            char *hex = "0123456789ABCDEF";
            test[11] = hex[(key >> 4) & 0x0F];
            test[12] = hex[key & 0x0F];
            for (uint16_t i = 0; test[i] != '\0'; i++)
                put_character(test[i]);
        }
        break;
    }

    return esp;
}