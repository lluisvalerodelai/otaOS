#include "global_descriptor_table.h"
#include "interrupt_descriptor_table.h"
#include "interrupt_requests.h"
#include "interrupt_service_routines_setup.h"
#include "peripheral_component_interconnect.h"
#include "keyboard.h"
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

	for (int bus = 0; bus < 255; bus++) {
		for (int dev = 0; dev < 32; dev++) {
			for (int func = 0; func < 8; func++) {
				struct pci_device_t foo = init_PCI_BDF(bus, dev, func); 
				pci_fill_info(&foo);
				pciPrintInfo(foo);
			}
		}
	}

  for (;;)
    ; // safety
}
