#include <common/stdint.h>
#include <gdt.h>
#include <hardware/idt.h>
#include <hardware/port.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/driver.h>
#include <drivers/video.h>
#include <task/task.h>
#include <task/kernel_task.h>

void kmain(void) {
    clear_screen();
    //kprint("Loading System...\n");
    init_gdt();
    set_gdt(gdt,sizeof(gdt));
    
    struct driver keyboard_driver = {init_keyboard, keyboard_handler};
    struct driver mouse_driver = {init_mouse, mouse_handler};
    
    idt_init();
    reload_segments();
    add_driver(KEYBOARD_INT, keyboard_driver);
    add_driver(MOUSE_INT, mouse_driver);
    init_drivers();
    
    while(1);
}