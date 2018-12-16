all:
	nasm -felf32 ./boot/bootloader.asm -o ./boot/bootloader.o
	i686-elf-gcc -c ./kernel/main.c -o ./kernel/main.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o ./images/fuseOS.bin -ffreestanding -O2 -nostdlib ./boot/bootloader.o ./kernel/main.o
	dd if=./images/fuseOS.bin bs=512 of=./images/fuseOS.img

