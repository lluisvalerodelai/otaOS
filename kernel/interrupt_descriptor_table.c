#include "sys.h"
#include "interrupt_descriptor_table.h"

struct idt_entry {
  uint16 base_lo;
  uint16 sel;
  uint8 always0;
  uint8 flags;
  uint16 base_hi;
} __attribute__((packed));

struct idt_ptr {
  uint16 limit;
  uint32 base;
} __attribute__((packed));

//make an idt of 256 entries
struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load(); //declared in boot.asm

void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags) {
	    /* We'll leave you to try and code this function: take the
    *  argument 'base' and split it up into a high and low 16-bits,
    *  storing them in idt[num].base_hi and base_lo. The rest of the
    *  fields that you must set in idt[num] are fairly self-
    *  explanatory when it comes to setup */
	idt[num].base_lo = (base & 0xFFFF); 						/*low 16 bits of base*/	
	idt[num].base_hi = (base >> 16) & 0xFFFF;				/*high 16 bits of base*/	
	
	idt[num].sel = sel;
	idt[num].flags = flags;
	idt[num].always0 = 0;
}

void idt_init() {
	idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
	idtp.base = (uint32) &idt;

	memset_sys(&idt, 0, sizeof(struct idt_entry) * 256);

	/*add extra isr here*/

	idt_load();
}
