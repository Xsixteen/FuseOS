#include <stddef.h>
#include <stdint.h>

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void _start() {

	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	const size_t index = 1 * VGA_WIDTH + 0;
	terminal_buffer[index] = vga_entry('H', terminal_color);
	terminal_buffer[index+1] = vga_entry('E', terminal_color);
	terminal_buffer[index+2] = vga_entry('L', terminal_color);
	terminal_buffer[index+3] = vga_entry('L', terminal_color);
	terminal_buffer[index+4] = vga_entry('O', terminal_color);
	terminal_buffer[index+5] = vga_entry(' ', terminal_color);
	terminal_buffer[index+6] = vga_entry('W', terminal_color);
	terminal_buffer[index+7] = vga_entry('O', terminal_color);
	terminal_buffer[index+8] = vga_entry('R', terminal_color);
	terminal_buffer[index+9] = vga_entry('L', terminal_color);
	terminal_buffer[index+10] = vga_entry('D', terminal_color);
	terminal_buffer[index+11] = vga_entry(' ', terminal_color);
	for (;;);
}
