#include "types.h"
#include "gdt.h"
#include "vga.h"

void kmain() {
	gdt_install();

	vga_print("GDT SUCCESFULLY INSTALLED YAYAYYAY");
	reset();
	vga_print("reset the screen");

  for (;;); // extra safety loop
}
