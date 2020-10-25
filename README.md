ONLY FOR EDUCATIONAL PURPOSES!

Implemented Features (x86):
- Global Descriptor Table
- Interrupt Descriptor Table
- Port Read/Write (8-16-32 Bits)
- Handling Exceptions
- Handling Interrupts
- Keyboard Handling in Text Mode
- Mouse Handling in Text Mode
- Some character functions in Text Mode

Will Implement Features (x86):
- x64 Global Descriptor Table Entry (If this is different from x86, not researched yet)
- x64 Interrupt Descriptor Table Entry (If this is different from x86, not researched yet)
- PCI
- Multitasking (Not even researched yet)
- Hard drive
- File System (FAT16)
- Dynamic Memory Management
- VGA Graphics Mode
- Desktop, Windows
- System Call Basics
- User Mode
- GUI Framework Basics
- Network Basics
- TCP, UDP
- HTTP Server, Client
- Basic Browser
- Maybe POSIX compatible things

How to run:
- Install QEMU (https://www.qemu.org/download/)
- git clone https://github.com/liveans/OperatingSystemEP
- cd OperatingSystemEP && make build-install

References:
- https://wiki.osdev.org/Main_Page (Mostly)
- https://github.com/danistefanovic/build-your-own-x (Operating System Part)

Bu repodaki her şeyi izin almadan, kaynak göstermeden, özgürce okuyabilir, başkalarına okutabilir, kopyalayabilir, dağıtabilir, başka bir dile çevirebilir, yayabilir, eleştirebilir, kendi etik ilkeleriniz doğrultusunda, çalabilir, talan edebilir, kısmen ya da tamamen sahiplenebilir, satabilir, değiştirerek ya da değiştirmeden tekrar yayımlayabilir, kötüleyebilir, lanetleyebilirsiniz.