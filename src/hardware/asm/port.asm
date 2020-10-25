bits 32

section .text
    global write_port_8bit
    global write_port_8bit_slow
    global write_port_16bit
    global write_port_32bit
    global read_port_8bit
    global read_port_16bit
    global read_port_32bit
write_port_8bit:
    xor     edx, edx
    xor     eax, eax
    mov     dx, [esp + 4]
    mov     al, [esp + 8]
    out     dx, al
    ret

write_port_8bit_slow:
    xor     edx, edx
    xor     eax, eax
    mov     dx, [esp + 4]
    mov     al, [esp + 8]
    out     dx, al
    jmp     test
    test:
    jmp     test1
    test1:
    ret

read_port_8bit:
    xor     edx, edx
    xor     eax, eax
    mov     dx, [esp + 4]
    in      al, dx
    ret

write_port_16bit:
    xor     edx,edx
    xor     eax, eax
    mov     dx, [esp + 4]
    mov     ax, [esp + 8]
    out     dx, ax
    ret

write_port_32bit:
    xor     edx, edx
    xor     eax, eax
    mov     dx, [esp + 4]
    mov     eax, [esp + 8]
    out     dx, eax
    ret

read_port_16bit:
    xor     edx, edx
    xor     eax, eax
    mov     dx, [esp + 4]
    in      ax, dx
    ret

read_port_32bit:
    xor     edx, edx
    xor     eax, eax
    mov     dx, [esp + 4]
    in      eax, dx
    ret
