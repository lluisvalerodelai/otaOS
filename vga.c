#include "vga.h"

uint16_t column = 0;
uint16_t line = 0;
uint16_t* const vga = (uint16_t* const) 0xB8000; //location of start of vram
const uint16_t defaultColor = ( COLOR8_BLACK << 8   // second 4 bytes for bg color
															| COLOR8_LIGHT_GREY << 12); //first 4 bytes for foreground color

void reset() {
	line = 0;
	column = 0;

	for (uint16_t y = 0; y < height; y++) {
		for (uint16_t x = 0; x < width; x ++) {
			vga[y * width + x] = defaultColor | ' ';
		}
	}
}

void newLine() {
	// if were not at the last line already, then increase line
	// else scroll screen and then add new line
	if (line < height - 1) {
		line += 1;
		column = 0;
	} else {
		scrollUp();
		column = 0;
	}
}

void scrollUp() {
	for (uint16_t y = 0; y < height; y++) {
		for (uint16_t x = 0; x < width; x++) {
			vga[(y-1) * width + x] = vga[y*width + x];
		}
	}

	for (uint16_t x = 0; x < width; x++) {
		vga[(height-1)*width + x] = defaultColor | ' ';
	}
}

void print(const char* str) {
	uint16_t i = 0;
	while (str[i] != '\0') {
		if (str[i] == '\n') {
			newLine();
		} else {
			if (column == width) {
				newLine();
			}

			vga[line*width + (column++)] = defaultColor | str[i];
		}
		i++;
	}
}
