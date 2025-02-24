#include "types.h"
#include "sys.h"
#include "vga.h"
#include "interrupt_descriptor_table.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void isrs_install() {
    idt_set_gate(0, (uint32) isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32)isr1, 0x08, 0x8E);
    idt_set_gate(2, (uint32)isr2, 0x08, 0x8E);
    idt_set_gate(3, (uint32)isr3, 0x08, 0x8E);
    idt_set_gate(4, (uint32)isr4, 0x08, 0x8E);
    idt_set_gate(5, (uint32)isr5, 0x08, 0x8E);
    idt_set_gate(6, (uint32)isr6, 0x08, 0x8E);
    idt_set_gate(7, (uint32)isr7, 0x08, 0x8E);
    idt_set_gate(8, (uint32)isr8, 0x08, 0x8E);
    idt_set_gate(9, (uint32)isr9, 0x08, 0x8E);
    idt_set_gate(10, (uint32)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32)isr31, 0x08, 0x8E);
}

char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

//all the exception handling routines point here for now
void fault_handler(struct regs *r) {
	if (r->int_no < 32){
		vga_print(exception_messages[r->int_no]);
		vga_print(" Exception happened, system halt\n");
		for(;;);
	}
}
