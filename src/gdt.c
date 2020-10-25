#include <common/stdint.h>
#include <gdt.h>

uint32_t my_tss[26] = {};

struct gdt_entry create_segment_descriptor(uint32_t address, uint32_t limit, uint8_t type) {
    struct gdt_entry entry = {0};
    if(limit > 0xFFFF && ((limit & 0xFFF) != 0xFFF)) {
        //Fatal Error!
    }
    entry.flags.my_bits.db_bit = 1;
    if(limit > 0xFFFF) {
        limit >>= 12;
        entry.flags.my_bits.g_bit = 1;
    }
    entry.segment_size_lower = limit & 0xFFFF;
    entry.flags.my_bits.segment_size_upper_nibble = (limit >> 16) & 0xF;

    entry.base_address_lower = address & 0xFFFF;
    entry.base_address_third = (address >> 16) & 0xFF;
    entry.base_address_higher = (address >> 24) & 0xFF;

    entry.type.byte = type;
    return entry;
}

struct gdt_entry gdt[GDT_SIZE] = {0};

void init_gdt(void) {
    gdt[0] = create_segment_descriptor(0, 0, 0);
    gdt[1] = create_segment_descriptor(0, 0xffffffff, 0x9A);
    gdt[2] = create_segment_descriptor(0, 0xffffffff, 0x92);
    gdt[3] = create_segment_descriptor(0, 0xffffffff, 0xFA);
    gdt[4] = create_segment_descriptor(0, 0xffffffff, 0xF2);
    //gdt[3] = create_segment_descriptor(&my_tss, sizeof(my_tss), 0x89);
}

uint32_t get_base_address(const struct gdt_entry *entry) {
    uint32_t result = entry->base_address_higher;
    result = (result << 8) + entry->base_address_third;
    result = (result << 16) + entry->base_address_lower;
    return result;
}

uint32_t get_limit(const struct gdt_entry *entry) {
    uint32_t result = entry->flags.my_bits.segment_size_upper_nibble & 0xF;
    result = (result << 16) + entry->segment_size_lower & 0xFFFF;
    return result;
}