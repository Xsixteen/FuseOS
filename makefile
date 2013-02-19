all:
	nasm ./boot/bootloader.asm -o ./boot/bootloader.o
	gcc -O2 -Wall -force_cpusubtype_ALL -arch i386 -c ./kernel/main.c ./lib/kprint.c 
	mv ./kprint.o ./lib/kprint.o
	mv ./main.o ./kernel/main.o
	ld -o fuseOS.bin ./boot/bootloader.o ./lib/kprint.o ./kernel/main.o
