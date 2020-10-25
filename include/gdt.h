#ifndef __GDT_H
#define __GDT_H

#include <common/stdint.h>

#define GDT_SIZE        5
union type {
    uint8_t byte;
    struct {
        uint8_t segment_type : 4;
        uint8_t s_bit : 1;
        uint8_t dpl_bits : 2;
        uint8_t p_bit : 1; 
    }__attribute__((packed)) my_bits;
};
union flags {
    uint8_t byte;
    struct {
        uint8_t segment_size_upper_nibble : 4;
        uint8_t avl_bit : 1;
        uint8_t zero_bit : 1;
        uint8_t db_bit : 1;
        uint8_t g_bit : 1;
    }__attribute__((packed)) my_bits;
};
struct gdt_entry {
    uint16_t segment_size_lower;
    uint16_t base_address_lower;
    uint8_t base_address_third;
    union type type;
    union flags flags;
    uint8_t base_address_higher;
} __attribute__((packed));

extern struct gdt_entry gdt[GDT_SIZE];
void set_gdt(struct gdt_entry* gdt_address, uint16_t limit);
void reload_segments(void);
void init_gdt(void);

#endif