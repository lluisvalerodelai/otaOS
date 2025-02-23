#include "global_descriptor_table.h"
#include "types.h"

/*
 * defines a single GDT entry
 */
struct gdt_entry {
  uint16 limit_low;
  uint16 base_low;
  uint8 base_middle;
  uint8 access;
  uint8 granularity;
  uint8 base_high;
} __attribute__((packed));

/*
 * pointer for the actual gdt struct, which is passed onto the gdt register
 */

struct gdt_ptr {
  uint16 limit;
  uint32 base;
} __attribute__((packed));

/*the gdt will have three entries, null, kernel code, kernel data*/
struct gdt_entry gdt[3];
struct gdt_ptr gp;

void gdt_set_gate(int num, uint32 base, uint32 limit, uint8 access,
                  uint8 gran) {

  /*setup the descriptor base address */
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  /* Setup the descriptor limits */
  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = ((limit >> 16) & 0x0F);

  /* Finally, set up the granularity and access flags */
  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;
}

/*this function is defined in boot.asm*/
/*properly reloads the new segment registers so that it doesent interfere with
 * grubs gdt*/
extern void gdt_flush();

void gdt_install() {
  /*set up gdt pointer and limit*/
  gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
  gp.base = (uint32)&gdt; // code smell

  /*null descriptor*/
  gdt_set_gate(0, 0, 0, 0, 0);

  /*
   * code segment entry
   * base address: 0
   * limit: 4gb
   * 4kb granularity (page size)
   * 32-bit opcodes
   * code segment descriptor
   */
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

  /* Data Segment.
   * same as the code segment, but the descriptor type in
   * this entry's access byte says it's a Data Segment */
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  /*flush the old gdt and install new changes*/
  gdt_flush();
}
