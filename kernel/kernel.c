#include "global_descriptor_table.h"
#include "interrupt_descriptor_table.h"
#include "interrupt_requests.h"
#include "interrupt_service_routines_setup.h"
#include "keyboard.h"
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

  // timer_counter_install();
	keyboard_init();

  vga_print("################################\n");
  vga_print("#           otaOS              #\n");
  vga_print("################################\n");

  // vga_print((char *) ((int) "hello" / 0));

  for (;;)
    ; // safety
}
