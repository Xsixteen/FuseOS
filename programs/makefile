all:
	i686-elf-gcc -c ./simple-program/simple-program.c -o ./simple-program/simple-program.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-ld ./simple-program/simple-program.o -o ./simple-program/simple-program.bin --oformat=elf32-i386 
	cp ./simple-program/simple-program.bin ../iso/modules

