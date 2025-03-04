#ifndef __PCI_H
#define __PCI_H

#include "types.h"

struct PCI_BDF {
	uint16 vendor_ID;
	uint16 device_ID;
	uint8 header_type;
	uint8 bus;
	uint8 device;
	uint8 func;
};

struct PCI_BDF init_PCI_BDF(uint8 bus, uint8 device, uint8 func);
uint16 pciConfigReadWord(struct PCI_BDF pci_device, uint8 offset);
uint8 pciIsValid(struct PCI_BDF device);
void pci_fill_info(struct PCI_BDF *device);
void pciPrintInfo(struct PCI_BDF device);

#endif // ! __PCI_H

