#!/bin/bash
mkdir -p build
/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -m32 -g -c k_graphics/maingraphics.c -o build/maingraphics.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -m32 -g -c k_math/mainmath.c -o build/mainmath.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -m32 -g -c k_system/mainsystem.c -o build/mainsystem.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -m32 -g -c k_strings/mainstrings.c -o build/mainstrings.o
/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -m32 -g -c k_system/memalloc.c -o build/memalloc.o 
/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -m32 -g -c kernel.c -o build/kernel.o
/usr/local/i386elfgcc/bin/i386-elf-ld -r build/kernel.o build/mainstrings.o build/mainsystem.o build/mainmath.o build/maingraphics.o build/memalloc.o -o build/full_kernel.o
nasm "kernel_entry.asm" -f elf -o "build/kernel_entry.o"
/usr/local/i386elfgcc/bin/i386-elf-ld -o "kernel.bin" -Ttext 0x7e00 "build/kernel_entry.o" "build/full_kernel.o" --oformat binary
nasm -f bin bootloader.asm -o bootloader.bin
dd if=/dev/zero of=disk.img bs=512 count=20480
dd if=bootloader.bin of=disk.img bs=512 count=1 conv=notrunc
dd if=kernel.bin of=disk.img bs=512 seek=1 count=1 conv=notrunc 
#dd if=../notpad.bin of=disk.img bs=512 seek=1 count=1 conv=notrunc 
qemu-system-x86_64 -drive format=raw,file=disk.img