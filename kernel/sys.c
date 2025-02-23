#include "sys.h"

void *memset_sys(void *dest, char val, int count) {
  char *temp = (char *)dest;
  for (; count != 0; count--)
    *temp++ = val;
  return dest;
}

/* We will use this to write to I/O ports to send bytes to devices. This
 *  will be used in the next tutorial for changing the textmode cursor
 *  position. Again, we use some inline assembly for the stuff that simply
 *  cannot be done in C */
void outportb(unsigned short port, unsigned char data) {
  __asm__ __volatile__("outb %1, %0" : : "dN"(port), "a"(data));
}
