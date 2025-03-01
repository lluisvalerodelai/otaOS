#include "sys.h"
#include "types.h"

void *memset_sys(void *dest, char val, int count) {
  char *temp = (char *)dest;
  for (; count != 0; count--)
    *temp++ = val;
  return dest;
}

/* write 1 byte to I/O ports to send bytes to devices. */
void outportb(uint16 port, uint8 data) {
  __asm__ __volatile__("outb %1, %0" : : "dN"(port), "a"(data));
}

/* read 1 byte from I/O ports*/
uint8 inportb(uint16 port) {
  unsigned char rv;
  __asm__ __volatile__("inb %1, %0" : "=a"(rv) : "dN"(port));
  return rv;
}

// Write 32-bit value to I/O port
void outportl(uint16 port, uint32 data) {
  __asm__ __volatile__(
      "outl %0, %1" // "outl" is the instruction to write a 32-bit value to an
                    // I/O port
      :             // No output operands
      : "a"(data),
        "d"(port) // Input operands: "a" is the accumulator register (EAX for
                  // 32-bit), "d" is the port register (EDX for I/O ports)
  );
}

// inl - Read 32-bit value from I/O port
uint32 inportl(uint16 port) {
    uint32 result;
    __asm__ __volatile__ (
        "inl %1, %0"         // "inl" is the instruction to read a 32-bit value from an I/O port
        : "=a" (result)      // Output operand: the result will be stored in the EAX register
        : "d" (port)         // Input operand: the I/O port address is in the EDX register
    );
    return result;
}
