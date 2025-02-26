#include "vga.h"
#include "types.h"

int width = 80;
int height = 25;
int curr_row = 0;
int curr_col = 0;

uint16 *vga = (uint16 *)0xB8000;

void reset() {
  /* resets the screen, clears all text */
  for (uint8 i = 0; i < height; i++) {
    for (uint8 j = 0; j < width; j++) {
      vga[width * i + j] = (uint16)0x0; // vram works in 2 byte chunks
    }
  }

  curr_col = 0;
  curr_row = 0;
}

void newline() {
  curr_col = 0;
	if (curr_row >= height) {
		scroll();
	}
  curr_row++;
}

void scroll() {
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width + 1; i++) {
      vga[(width * j) + i] = vga[(width * (j + 1)) + i];
    }
  }
}

void vga_putc(const char c) {
  vga[(curr_row * width) + curr_col] = (0x07 << 8) | c;
  curr_col++;
}

void vga_print(const char *str) {
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == '\n') {
      newline();
      i++;
    } else {
      vga_putc(str[i]);
      i++;
    }
  }
}
