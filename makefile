all:
	nasm ./boot/bootloader.asm -o ./boot/bootloader.o
	gcc -c ./kernel/main.c ./lib/kprint.c 
	mv ./kprint.o ./lib/kprint.o
	mv ./main.o ./kernel/main.o
	ld -T Link.ld -o ./Images/fuseOS.bin ./boot/bootloader.o ./lib/kprint.o ./kernel/main.o
	dd if=./Images/fuseOS.bin bs=512 of=./Images/fuseOS.img
