#include "system.h"
#include "types.h"

int width = 80;
int height = 20;
int curr_row = 0;
int curr_col = 0;

uint16 *vga = (uint16 *)0xB8000;

void print(const char *str) {
	int i = 0;
  while (str[i] != '\0') {
    vga[curr_row * width + curr_col] = (0x0F << 8) | str[i];
		if (curr_col > 80) {
			curr_col = 0;
			curr_row= curr_row + 1;
		} else {
			curr_col++;
		}
		i++;
  }
}

void kmain() {
  /* commands go here */

	print("hello world! \n");

  for (;;)
    ; // safety final loop
}
