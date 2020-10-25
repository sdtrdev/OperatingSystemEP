bits 32

section .bss
    gdtr dw 0
         dd 0

section .text
    global set_gdt
    global reload_segments
    global set_idtr
    global load_idt
    global keyboard_handler
    extern keyboard_handler_main

set_gdt:                    ; set_gdt(gdt, sizeof(gdt));
    mov     eax, [esp + 4]  ; get pointer of global descriptor table to register
    mov     [gdtr + 2], eax ; set gdtr's higher 32 bit with gdt address from register

    mov     ax, [esp + 8]
    mov     [gdtr], ax
    lgdt    [gdtr]
    ret

reload_segments:
    mov     ax, 0x10
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    jmp     0x08:.flush
    .flush:
        ret

load_idt:
    mov     edx, [esp + 4]
    lidt    [edx]
    sti
    ret