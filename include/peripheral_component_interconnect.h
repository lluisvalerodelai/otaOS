#ifndef _PCI_H
#define _PCI_H

#include "types.h"

struct pci_device_t {
  uint16 vendor_ID;
  uint16 device_ID;
  uint8 header_type;
  uint8 bus;
  uint8 device;
  uint8 func;
};

struct pci_device_t init_PCI_BDF(uint8 bus, uint8 device, uint8 func);
uint16 pciConfigReadWord(struct pci_device_t pci_device, uint8 offset);

void pciConfigWriteWord(struct pci_device_t pci_device, uint8 offset,
                        uint16 value);

uint8 pciIsValid(struct pci_device_t device);
void pci_fill_info(struct pci_device_t *device);
void pciPrintInfo(struct pci_device_t device);
void pci_main();

#endif // ! __PCI_H
