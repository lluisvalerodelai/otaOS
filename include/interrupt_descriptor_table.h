#ifndef _IDT_H
#define _IDT_H

#include "types.h"
void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags); 
void idt_init(); 

#endif // !_IDT_H
