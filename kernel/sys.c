#include "sys.h"

void *memset_sys(void *dest, char val, int count) {
  char *temp = (char *)dest;
  for (; count != 0; count--)
    *temp++ = val;
  return dest;
}

/* write to I/O ports to send bytes to devices. */
void outportb(unsigned short port, unsigned char data) {
  __asm__ __volatile__("outb %1, %0" : : "dN"(port), "a"(data));
}
