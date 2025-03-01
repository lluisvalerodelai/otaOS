#ifndef __PCI_H
#define __PCI_H

#include "types.h"

uint16 pciConfigReadWord(uint8 bus, uint8 slot, uint8 func, uint8 offset);
uint16 pciCheckVendor(uint8 bus, uint8 slot);

#endif // ! __PCI_H

