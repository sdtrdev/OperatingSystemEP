bits 32

section .text
    extern handle_interrupts
    global ignore_interrupt_request
    extern put_character
%define IRQ_BASE 0x20

%macro handle_interrupt_request 1
    global handle_interrupt_request_%1
    handle_interrupt_request_%1:
        mov byte [interrupt_no], %1 + IRQ_BASE
        jmp int_bottom
%endmacro

%macro handle_exception 1
    global handle_exception_%1
    handle_exception_%1:
        mov byte [interrupt_no], %1
        jmp int_bottom
%endmacro

handle_interrupt_request 0x00
handle_interrupt_request 0x01
handle_interrupt_request 0x02
handle_interrupt_request 0x03
handle_interrupt_request 0x04
handle_interrupt_request 0x05
handle_interrupt_request 0x06
handle_interrupt_request 0x07
handle_interrupt_request 0x08
handle_interrupt_request 0x09
handle_interrupt_request 0x0A
handle_interrupt_request 0x0B
handle_interrupt_request 0x0C
handle_interrupt_request 0x0D
handle_interrupt_request 0x0E
handle_interrupt_request 0x0F

handle_exception 0x00
handle_exception 0x01
handle_exception 0x02
handle_exception 0x03
handle_exception 0x04
handle_exception 0x05
handle_exception 0x06
handle_exception 0x07
handle_exception 0x08
handle_exception 0x09
handle_exception 0x0A
handle_exception 0x0B
handle_exception 0x0C
handle_exception 0x0D
handle_exception 0x0E
handle_exception 0x0F
handle_exception 0x10
handle_exception 0x11
handle_exception 0x12
handle_exception 0x13


int_bottom:
    pusha 
    push   ds
    push   es
    push   fs
    push   gs

    push   esp
    push   dword [interrupt_no]
    call   handle_interrupts
    mov    esp, eax

    pop    gs
    pop    fs
    pop    es
    pop    ds
    popa
ignore_interrupt_request:
    iret

section .data
    interrupt_no    db  0
