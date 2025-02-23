#include "gdt.h"
#include "types.h"
#include "vga.h"

void kmain() {
  gdt_install();

  vga_print("GDT SUCCESFULLY INSTALLED");
  reset();

	vga_print("hello world! \nI just did a newline!");


  for (;;); // safety
}
