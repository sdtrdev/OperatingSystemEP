#include <hardware/port.h>
#include <common/stdint.h>
#include <common/stdlib.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/driver.h>

void load_idt(uint32_t*);
void put_character(char);

#define IDT_SIZE        256
#define RESERVED_SIZE   0x20

#define PIC1_COMMAND    0x20
#define PIC1_DATA       0x21

#define PIC2_COMMAND    0xA0
#define PIC2_DATA       0xA1

#define IDT_INT_GATE    0xE

#define USER_LEVEL      0x3
#define SUPER_LEVEL     0x0

#define handle_interrupt_request(x)     void handle_interrupt_request_##x(void)
#define handle_exception(x)     void handle_exception_##x(void)

#define CODE_SEGMENT    0x08

typedef struct tagIDT_ENTRY {
    uint16_t offset_lower_bits;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attribute;
    uint16_t offset_higher_bits;
} IDT_ENTRY;

void ignore_interrupt_request(void);
handle_interrupt_request(0x00);
handle_interrupt_request(0x01);
handle_interrupt_request(0x02);
handle_interrupt_request(0x03);
handle_interrupt_request(0x04);
handle_interrupt_request(0x05);
handle_interrupt_request(0x06);
handle_interrupt_request(0x07);
handle_interrupt_request(0x08);
handle_interrupt_request(0x09);
handle_interrupt_request(0x0A);
handle_interrupt_request(0x0B);
handle_interrupt_request(0x0C);
handle_interrupt_request(0x0D);
handle_interrupt_request(0x0E);
handle_interrupt_request(0x0F);


handle_exception(0x00);
handle_exception(0x01);
handle_exception(0x02);
handle_exception(0x03);
handle_exception(0x04);
handle_exception(0x05);
handle_exception(0x06);
handle_exception(0x07);
handle_exception(0x08);
handle_exception(0x09);
handle_exception(0x0A);
handle_exception(0x0B);
handle_exception(0x0C);
handle_exception(0x0D);
handle_exception(0x0E);
handle_exception(0x0F);
handle_exception(0x10);
handle_exception(0x11);
handle_exception(0x12);
handle_exception(0x13);


IDT_ENTRY IDT[IDT_SIZE];

uint32_t handle_interrupts(uint8_t interrupt_no, uint32_t esp) {
    driver_handler handler = get_handler(interrupt_no);
    if(handler != NULL)
        esp = handler(esp);
    
    else if(interrupt_no != 0x20) {
        char test[] = "UNHANDLED INTERRUPT 0x00 ";
        char* hex = "0123456789ABCDEF";
        test[22] = hex[(interrupt_no >> 4) & 0x0F];
        test[23] = hex[interrupt_no & 0x0F];
        for (uint16_t i = 0; test[i] != '\0'; i++)
            put_character(test[i]);
    }
    
    if(0x20 <= interrupt_no && interrupt_no < 0x30) {
        write_port_8bit(PIC1_COMMAND, 0x20);
        if(0x28 <= interrupt_no)
            write_port_8bit(PIC2_COMMAND, 0x20);
    }
    return esp;
}

void set_interrupt_descriptor_table_entry(
    uint8_t interrupt_no,
    uint16_t code_segment_selector_offset,
    void (*handler)(void),
    uint8_t descriptor_priv_level,
    uint8_t descriptor_type
) {
    IDT[interrupt_no].offset_lower_bits = ((uint32_t)handler) & 0xFFFF;
    IDT[interrupt_no].offset_higher_bits = (((uint32_t)handler & 0xFFFF0000) >> 16);
    IDT[interrupt_no].selector = code_segment_selector_offset;
    IDT[interrupt_no].zero = 0;
    IDT[interrupt_no].type_attribute = 0x80 | ((descriptor_priv_level & 3) << 5) | descriptor_type;
}

void idt_init(void) {
    uint32_t idt_address;
    uint32_t idt_ptr[2];
    int i;
    for(i = 255; i > 0; --i)
        set_interrupt_descriptor_table_entry(i, CODE_SEGMENT, ignore_interrupt_request, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0, CODE_SEGMENT, ignore_interrupt_request, SUPER_LEVEL, IDT_INT_GATE);

    set_interrupt_descriptor_table_entry(0x00, CODE_SEGMENT, handle_exception_0x00, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x01, CODE_SEGMENT, handle_exception_0x01, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x02, CODE_SEGMENT, handle_exception_0x02, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x03, CODE_SEGMENT, handle_exception_0x03, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x04, CODE_SEGMENT, handle_exception_0x04, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x05, CODE_SEGMENT, handle_exception_0x05, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x06, CODE_SEGMENT, handle_exception_0x06, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x07, CODE_SEGMENT, handle_exception_0x07, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x08, CODE_SEGMENT, handle_exception_0x08, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x09, CODE_SEGMENT, handle_exception_0x09, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x0A, CODE_SEGMENT, handle_exception_0x0A, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x0B, CODE_SEGMENT, handle_exception_0x0B, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x0C, CODE_SEGMENT, handle_exception_0x0C, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x0D, CODE_SEGMENT, handle_exception_0x0D, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x0E, CODE_SEGMENT, handle_exception_0x0E, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x0F, CODE_SEGMENT, handle_exception_0x0F, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x10, CODE_SEGMENT, handle_exception_0x10, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x11, CODE_SEGMENT, handle_exception_0x11, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x12, CODE_SEGMENT, handle_exception_0x12, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x13, CODE_SEGMENT, handle_exception_0x13, SUPER_LEVEL, IDT_INT_GATE);

    set_interrupt_descriptor_table_entry(0x20, CODE_SEGMENT, handle_interrupt_request_0x00, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x21, CODE_SEGMENT, handle_interrupt_request_0x01, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x22, CODE_SEGMENT, handle_interrupt_request_0x02, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x23, CODE_SEGMENT, handle_interrupt_request_0x03, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x24, CODE_SEGMENT, handle_interrupt_request_0x04, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x25, CODE_SEGMENT, handle_interrupt_request_0x05, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x26, CODE_SEGMENT, handle_interrupt_request_0x06, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x27, CODE_SEGMENT, handle_interrupt_request_0x07, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x28, CODE_SEGMENT, handle_interrupt_request_0x08, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x29, CODE_SEGMENT, handle_interrupt_request_0x09, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x2A, CODE_SEGMENT, handle_interrupt_request_0x0A, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x2B, CODE_SEGMENT, handle_interrupt_request_0x0B, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x2C, CODE_SEGMENT, handle_interrupt_request_0x0C, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x2D, CODE_SEGMENT, handle_interrupt_request_0x0D, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x2E, CODE_SEGMENT, handle_interrupt_request_0x0E, SUPER_LEVEL, IDT_INT_GATE);
    set_interrupt_descriptor_table_entry(0x2F, CODE_SEGMENT, handle_interrupt_request_0x0F, SUPER_LEVEL, IDT_INT_GATE);

    write_port_8bit(PIC1_COMMAND, 0x11);
    write_port_8bit(PIC2_COMMAND, 0x11);

    write_port_8bit(PIC1_DATA, 0x20);
    write_port_8bit(PIC2_DATA, 0x28);

    write_port_8bit(PIC1_DATA, 0x04);
    write_port_8bit(PIC2_DATA, 0x02);

    write_port_8bit(PIC1_DATA, 0x01);
    write_port_8bit(PIC2_DATA, 0x01);

    write_port_8bit(PIC1_DATA, 0x00);
    write_port_8bit(PIC2_DATA, 0x00);

    idt_address = (unsigned long)IDT;
    idt_ptr[0] = (sizeof(IDT_ENTRY) * IDT_SIZE) +((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}
