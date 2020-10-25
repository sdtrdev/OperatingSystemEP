#ifndef __TASK_H
#define __TASK_H

#include <common/stdlib.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>

struct task {
    struct keyboard_event* keyboard;
    struct mouse_event* mouse;
};

void set_focused_task(struct task *task);
struct task* get_focused_task(void);

#endif