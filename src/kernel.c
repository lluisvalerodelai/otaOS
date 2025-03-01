#include "global_descriptor_table.h"
#include "interrupt_descriptor_table.h"
#include "interrupt_requests.h"
#include "interrupt_service_routines_setup.h"
#include "peripheral_component_interconnect.h"
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
	vga_print("testing PCI addresses \n");
	vga_print("bus: 0\n");
	vga_print("device 2\n");
	vga_print("function: 0 \n");

	uint16 vendor = pciCheckVendor(0, 2);
	if (vendor == 0x1234) {
		vga_print("returned woahhh\n");
	} else {
		vga_print("actually something, time to implement printf yay");
	}

  for (;;)
    ; // safety
}
