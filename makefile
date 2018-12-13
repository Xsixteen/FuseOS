all:
	nasm -felf32 ./boot/bootloader.asm -o ./boot/bootloader.o
	gcc -m32 -c ./kernel/main.c
	gcc -T linker.ld -o ./images/fuseOS.bin -ffreestanding -O2 -nostdlib ./boot/bootloader.o ./main.o
	dd if=./images/fuseOS.bin bs=512 of=./images/fuseOS.img
