#ifndef __KERNEL_TASK_H
#define __KERNEL_TASK_H

#include <task/task.h>

void on_key_down(char);
void on_key_up(char);

void on_mouse_move(int32_t offset_x,int32_t offset_y);
void on_mouse_down(uint8_t button);
void on_mouse_up(uint8_t button);
void on_mouse_init(void);

#endif