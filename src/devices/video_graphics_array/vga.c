#include "vga.h"
#include "sys.h"
#include "types.h"
#include "types.h"

#define UP_ARROW 0x06
#define DOWN_ARROW 0x03
#define LEFT_ARROW 0x04
#define RIGHT_ARROW 0x05

int width = 80;
int height = 25;
int curr_row = 0;
int curr_col = 0;

uint16 *vga = (uint16 *)0xB8000;

void disable_cursor() {
  outportb(0x3D4, 0x0A);
  outportb(0x3D5, 0x20);
}

void enable_cursor(uint8 cursor_start, uint8 cursor_end) {
  outportb(0x3D4, 0x0A);
  outportb(0x3D5, (inportb(0x3D5) & 0xC0) | cursor_start);

  outportb(0x3D4, 0x0B);
  outportb(0x3D5, (inportb(0x3D5) & 0xE0) | cursor_end);
}

void update_cursor(int row, int column) {
  int16 pos = row * width + column;

  outportb(0x3D4, 0x0F);
  outportb(0x3D5, (uint8)(pos & 0xFF));
  outportb(0x3D4, 0x0E);
  outportb(0x3D5, (uint8)((pos >> 8) & 0xFF));
}

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
  // for (int i = 0; i < width; i++) {
  // 	vga[width * height + i] = (uint16)0x0;
  // }
}

void vga_putc(const char c) {
  if (c == '\n') {
    newline();
		update_cursor(curr_row, curr_col);
    return;
  }

  if (c == '\b') {
    if (curr_col > 0) {
      curr_col--;
    } else if (curr_row > 0) {
      curr_col = width;
      curr_row--;
    }

    vga[(curr_row * width) + curr_col] = (0x07 << 8) | 0;
		update_cursor(curr_row, curr_col);
    return;
  }

  if (c == UP_ARROW) {
    if (curr_row >= 0) {
      curr_row--;
    }
		update_cursor(curr_row, curr_col);
    return;
  }

  if (c == DOWN_ARROW) {
    if (curr_row < height) {
      curr_row++;
    }
		update_cursor(curr_row, curr_col);
    return;
  }

  if (c == LEFT_ARROW) {
    if (curr_col > 0) {
      curr_col--;
    }
		update_cursor(curr_row, curr_col);
    return;
  }

  if (c == RIGHT_ARROW) {
    if (curr_col < width) {
      curr_col++;
    }
		update_cursor(curr_row, curr_col);
    return;
  }

  vga[(curr_row * width) + curr_col] = (0x07 << 8) | c;
  curr_col++;

	update_cursor(curr_row, curr_col);
}

void vga_print(const char *str) {
  int i = 0;
  while (str[i] != '\0') {
    vga_putc(str[i]);
    i++;
  }
}
