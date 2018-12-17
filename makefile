all:
	nasm -felf32 ./bootloader/bootloader.asm -o ./bootloader/bootloader.o
	nasm -felf32 ./kernel/asm/irqhandlers.asm -o ./kernel/asm/irqhandlers.o
	i686-elf-gcc -c ./kernel/main.c -o ./kernel/main.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c ./kernel/terminal.c -o ./kernel/terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c ./kernel/interrupt.c -o ./kernel/interrupt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o ./images/fuseOS.bin -ffreestanding -O2 -nostdlib ./bootloader/bootloader.o ./kernel/main.o ./kernel/terminal.o ./kernel/interrupt.o ./kernel/asm/irqhandlers.o 
	cp ./images/fuseOS.bin ./iso/boot/fuseOS.bin
	grub-mkrescue -o fuseOS.iso iso

