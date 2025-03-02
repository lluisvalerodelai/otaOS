#ifndef __PCI_H
#define __PCI_H

#include "types.h"

uint16 pciConfigReadWord(uint8 bus, uint8 device, uint8 func, uint8 offset);
uint16 pciGetVD(uint8 bus, uint8 device, uint8 function, uint16* deviceID);
uint16 pciCheckClassCode(uint8 bus, uint8 device, uint8 function);
void pciPrintInfo(uint8 bus, uint8 device, uint8 function);
uint16 pciGetVendorID(uint8 bus, uint8 device, uint8 function);
uint16 pciGetDeviceID(uint8 bus, uint8 device, uint8 function);;

#endif // ! __PCI_H

