#include "types.h"
#include "vga.h"

int width = 80;
int height = 20;
int curr_row = 0;
int curr_col = 0;

uint16 *vga = (uint16 *)0xB8000;

void reset() {
	/* resets the screen, clears all text */
	for (uint8 i = 0; i < height; i++) {
		for (uint8 j = 0; j < width; j++) {
			vga[width * i + j] = (uint16) 0; //vram works in 2 byte chunks
		}
	}

	curr_col = 0;
	curr_row = 0;
}

void scroll() {
	
}

void newline() {

}

void vga_print(const char *str) {
	int i = 0;
  while (str[i] != '\0') {
    vga[width * curr_row + curr_col] = (0x0F << 8) | str[i];
		if (curr_col > 80) {
			curr_col = 0;
			curr_row= curr_row + 1;
		} else {
			curr_col++;
		}
		i++;
  }
}
