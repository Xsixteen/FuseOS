#include "io.h"
#include "terminal.h"
#include "interrupt.h"
#include "global.h"
#include "../include/multiboot.h"

#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

multiboot_info_t *mbinfo;

void kernel_main(unsigned int ebx)
{
        mbinfo = (multiboot_info_t *) ebx;
        // module_address 		 = mbinfo->mods_addr;

	/* Initialize terminal interface */
	terminal_initialize();
	idt_init();

	/* Newline support is left as an exercise. */
	terminal_writestring("FuseOS v.0.0.1\n");
	terminal_writestring("Enabling Interrupts\n");
	if(mbinfo->mods_count == 1) {
		terminal_writestring("Module Count = 1, Sample Program can be loaded\n");	
	}
	for(;;);
}
