GCCPARAMS = -m32 -Iinclude -nostdlib -nodefaultlibs
NASMPARAMS = -f elf32
LDPARAMS = -m elf_i386

objects = obj/main.o \
		  obj/kernel.o \
		  obj/hardware/asm/port.o \
		  obj/drivers/driver.o \
		  obj/hardware/asm/setup.o \
		  obj/gdt.o \
		  obj/hardware/idt.o \
		  obj/hardware/asm/interrupt.o \
		  obj/drivers/keyboard.o \
		  obj/drivers/mouse.o \
		  obj/drivers/video.o \
		  obj/task/kernel_task.o \
		  obj/task/task.o

obj/%.o: src/%.c
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.asm
	mkdir -p $(@D)
	nasm $(NASMPARAMS) $< -o $@

bin/kernel: linker.ld $(objects)
	mkdir -p $(@D)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

run:
	qemu-system-i386 -kernel bin/kernel

clean:
	rm -rf obj bin kernel

build-install:
	make
	make kernel
	make run
