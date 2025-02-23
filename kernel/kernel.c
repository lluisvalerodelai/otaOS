#include "global_descriptor_table.h"
#include "interrupt_descriptor_table.h"
#include "interrupt_service_routines_setup.h"
#include "vga.h"

void kmain() {
  gdt_install();
  idt_init();

	isrs_install();

  vga_print("GDT SUCCESFULLY INSTALLED\n");

  vga_print("################################\n");
  vga_print("#           otaOS              #\n");
  vga_print("################################\n");
	
	vga_print((char *) ((int) "hello" / 0));

  vga_print("hello world! \nI just did a newline!");

  for (;;); // safety
}
