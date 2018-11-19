## Final Lab - Minimal example kernel for x86 architecture

### Instructions

https://wiki.osdev.org/User:Zesterer/Bare_Bones  

Follow the tutorial in the above link to create your first functional kernel that can be booted in an emulator as qemu. 

### Building the GCC cross-compiler for the i686-elf

`chmod +x gcc-compiler.sh`
`./gcc-compiler.sh`

### Installing QEMU 

`sudo apt-get install qemu-system`

### Compiling and linking

`i686-elf-gcc -std=gnu99 -ffreestanding -g -c start.s -o start.o`

`i686-elf-gcc -std=gnu99 -ffreestanding -g -c kernel.c -o kernel.o`

`i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld start.o kernel.o -o mykernel.elf -lgcc`

### Running with QEMU

`qemu-system-i386 -kernel mykernel.elf`
