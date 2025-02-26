#include "global_descriptor_table.h"
#include "interrupt_descriptor_table.h"
#include "interrupt_requests.h"
#include "interrupt_service_routines_setup.h"
#include "timer.h"
#include "vga.h"

void kmain() {

  gdt_install();
  // vga_print("GDT SUCCESFULLY INSTALLED\n");

  idt_init();
  isrs_install();
  irq_install();
  __asm__ __volatile__("sti"); // FINALLY start interrupts

  vga_print("IDT SUCCESFULLY INSTALLED\n");

  timer_counter_install();

  vga_print("################################\n");
  vga_print("#           otaOS              #\n");
  vga_print("################################\n");

  // vga_print((char *) ((int) "hello" / 0));

  vga_print("hello world! \nI just did a newline!");
	
	vga_print("hello world!\nhe");
	scroll();

  for (;;)
    ; // safety
}
