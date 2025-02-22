#include "types.h"

struct GDT {
    uint32_t base;
    uint32_t limit;
    uint8_t access_byte;
    uint8_t flags;
};

// GDT Array
uint8_t gdt[8 * 7];  // We are encoding 7 entries, each 8 bytes

// Utility function to encode a GDT entry
void encodeGdtEntry(uint8_t *target, struct GDT source)
{

    // Encode the limit (lower 16 bits)
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;

    // Encode the base (lower 24 bits)
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    // Encode the access byte
    target[5] = source.access_byte;

    // Encode the flags (shifted to the higher bits)
    target[6] |= (source.flags << 4);
}

void setupGDT() {
    // Null Descriptor (entry 0)
    struct GDT null_desc = { 0, 0, 0x00, 0x00 };
    encodeGdtEntry(&gdt[0], null_desc);  // Null descriptor

    // Kernel Mode Code Segment (entry 1)
    struct GDT kernel_code_desc = { 0x0, 0xFFFFF, 0x9A, 0x0C };
    encodeGdtEntry(&gdt[8], kernel_code_desc);

    // Kernel Mode Data Segment (entry 2)
    struct GDT kernel_data_desc = { 0x0, 0xFFFFF, 0x92, 0x0C };
    encodeGdtEntry(&gdt[16], kernel_data_desc);

    // User Mode Code Segment (entry 3)
    struct GDT user_code_desc = { 0x0, 0xFFFFF, 0xFA, 0x0C };
    encodeGdtEntry(&gdt[24], user_code_desc);

    // User Mode Data Segment (entry 4)
    struct GDT user_data_desc = { 0x0, 0xFFFFF, 0xF2, 0x0C };
    encodeGdtEntry(&gdt[32], user_data_desc);

    // // Task State Segment (TSS) (entry 5)
    // uint32_t tss_base = (uint32_t)&TSS;  // Address of TSS (make sure TSS is defined somewhere)
    // uint32_t tss_limit = sizeof(TSS) - 1;  // Size of TSS
    // struct GDT tss_desc = { tss_base, tss_limit, 0x89, 0x00 };
    // encodeGdtEntry(&gdt[40], tss_desc);
}

void initGDT() {
	__asm__ volatile(
		"gdtr: \
		 DW 0 ; For limit storage \
     DD 0 ; For base storage \
\
setGdt: \
   MOV   AX, [esp + 4] \
   MOV   [gdtr], AX \
   MOV   EAX, [ESP + 8] \
   MOV   [gdtr + 2], EAX \
   LGDT  [gdtr] \
   RET" \
	);
}

