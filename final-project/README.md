## Final Lab - Minimal example kernel for x86 architecture

### Compiling and running with QEMU

`i686-elf-gcc -std=gnu99 -ffreestanding -g -c start.s -o start.o`

`i686-elf-gcc -std=gnu99 -ffreestanding -g -c kernel.c -o kernel.o`
