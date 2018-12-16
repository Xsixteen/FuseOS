all:
	nasm -felf32 ./bootloader/bootloader.asm -o ./bootloader/bootloader.o
	i686-elf-gcc -c ./kernel/main.c -o ./kernel/main.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o ./images/fuseOS.bin -ffreestanding -O2 -nostdlib ./bootloader/bootloader.o ./kernel/main.o
	cp ./images/fuseOS.bin ./iso/boot/fuseOS.bin
	grub-mkrescue -o fuseOS.iso iso

