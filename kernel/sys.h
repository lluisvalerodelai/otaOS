#ifndef _SYS_H
#define _SYS_H

void *memset_sys(void *dest, char val, int count);

struct regs {
  unsigned int gs, fs, es, ds; /* pushed the segs last */
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by 'pusha' */
  unsigned int int_no, err_code; /* our 'push byte #' and ecodes do this */
  unsigned int eip, cs, eflags, useresp, ss; /* pushed by the processor automatically */
};

#endif // !_SYS_H
