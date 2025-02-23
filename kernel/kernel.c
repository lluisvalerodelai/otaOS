#include "types.h"
#include "vga.h"

void kmain() {
	vga_print("hello world!");

  for (;;); // extra safety loop
}
