#include "vga.h"
#include "types.h"

int width = 80;
int height = 20;
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

void scroll() {
  // scroll the screen up by one row
  for (uint8 i = 0; i < height - 1; i++) {
    for (uint8 j = 0; j < width; j++) {
      vga[width * i + j] = vga[width * (i + 1) + j];
    }
  }
}

void newline() {
  // set the cursor on a newline, and scroll if necessary
  if (curr_row == height - 1) {
    scroll();
  }
  curr_col = 0;
  curr_row++;
}

// also test out removing the \0 after you make the string in kmain
void vga_print(const char *str) {
  int i = 0;
  while (str[i] != '\0') {

    if (str[i] == '\n') {
      i++;
      newline();
      continue;
    }

    vga[curr_row * width + curr_col] = (0x07 << 8) | str[i];

    if (curr_col == width - 1) {
      newline();
    } else {
      curr_col += 1;
    }
    i++;
  }
}
