#include <task/kernel_task.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>

static struct keyboard_event keyboard = { on_key_down, on_key_up };
static struct mouse_event mouse = { on_mouse_down, on_mouse_up, on_mouse_move, on_mouse_init };
struct task kernel_task = { &keyboard, &mouse };
struct task *focused_task = &kernel_task;

void set_focused_task(struct task *task) {
    focused_task = task;
}

struct task* get_focused_task(void) {
    return focused_task;
}