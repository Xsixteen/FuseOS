#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
#include "io.h"

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

int commandBufferIndex = 0;
unsigned char commandBuffer[128];

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}


size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	if(c != '\n' && c != '\r') {
		if(c >= ' ') {
			terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
			
			if (++terminal_column == VGA_WIDTH) {
				terminal_column = 0;
			
				if (++terminal_row == VGA_HEIGHT)
					terminal_row = 0;
			}
		}
	}
	if( c== '\n' || c == '\r') {
		if (++terminal_row == VGA_HEIGHT)
                        terminal_row = 0;
		
		terminal_column = 0;
	} 
	
	if(c == '\b') {
		if(terminal_column > 0) {
			terminal_putentryat(' ', terminal_color, terminal_column-1, terminal_row);
			terminal_column --;
			update_cursor(terminal_column, terminal_row);
			commandBuffer[commandBufferIndex-1] = NULL;
			commandBufferIndex --;
		}
	}
}

void terminal_write(char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
	update_cursor(terminal_column, terminal_row);
}

void terminal_keyboard_hook() {
        unsigned char scanCode     = inb(0x60);
	char result 		   = kbdus[scanCode];
	terminal_putchar(result);
	if(result >= ' ') {
		commandBuffer[commandBufferIndex] = result;
		commandBufferIndex++;
	}
	if(result == '\r' || result =='\n') {
		terminal_command();
	}
	update_cursor(terminal_column, terminal_row);
}

void update_cursor(int x, int y) {
	uint16_t pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void terminal_command() {
	terminal_writestring("Writing Command\n");
	terminal_write(commandBuffer,128);
	if(strcmp(commandBuffer,"cls") == 0) {
		terminal_writestring("\ncls called");
		clear_screen();
	}
	terminal_writestring("\n");
	clearCommandBuffer();
}

void clearCommandBuffer() {
	for(int i = 0; i < 128; i++) {
		commandBuffer[i]  = NULL;
	}
	commandBufferIndex=0;
	
}

int strcmp(char * data1, char* data2) {
	for(int i =0; i < strlen(data2); i++){
		if(data1[i] != data2[i]) {
			return -1;
		}	
	}
	
	return 0;
}

void clear_screen() {

	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	update_cursor(0,0);
	terminal_column = 0;
	terminal_row    = 0;
}

