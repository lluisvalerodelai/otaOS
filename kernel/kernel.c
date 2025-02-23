#include "gdt.h"
#include "idt.h"
#include "vga.h"

void kmain() {
  gdt_install();
	idt_init();

  vga_print("GDT SUCCESFULLY INSTALLED");
  reset();

	vga_print("################################\n");
	vga_print("#           otaOS              #\n");
	vga_print("################################\n");

	vga_print("hello world! \nI just did a newline!");

  for (;;); // safety
}
