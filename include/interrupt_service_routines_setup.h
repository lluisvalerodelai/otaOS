#ifndef _ISRS_H
#define _ISRS_H

void isrs_install();
void fault_handler(struct regs *r);

#endif // !_ISRS_H
