#include "peripheral_component_interconnect.h"
#include "format_print.h"
#include "sys.h"
#include "types.h"

#define PCI_CONFIG_ADDRESS 0XCF8 // two 32 bit IO locations
#define PCI_CONFIG_DATA 0XCFC

/*
 * for specifying the specific PCI bus:device:function you need to write the
 * following to PCI_CONFIG_ADDRESS
 * +----------+----------+------------+-------------+------------+----------+
 * | Bit 31   | Bits 30-24| Bits 23-16 | Bits 15-11  | Bits 10-8 | Bits 7-0 |
 * +----------+----------+------------+-------------+------------+----------+
 * | Enable Bit| Reserved | Bus # | Device # | Function # | Register Offset |
 * +----------+----------+------------+-------------+--------------+--------+
 */

struct PCI_BDF init_PCI_BDF(uint8 bus, uint8 device, uint8 func) {
  struct PCI_BDF pci_device = {.device_ID = 0,
                               .device_ID = 0,
                               .bus = bus,
                               .device = device,
                               .func = func};
  return pci_device;
}

uint16 pciConfigReadWord(struct PCI_BDF pci_device, uint8 offset) {
  uint32 address; // the address offset to get to the 256 byte region that is
                  // allocated for some specific device on the PCI
  uint32 lbus = (uint32)pci_device.bus;
  uint32 lslot = (uint32)pci_device.device;
  uint32 lfunc = (uint32)pci_device.func;
  uint16 tmp = 0;

  address = (uint32)((lbus << 16) | (lslot << 11) | (lfunc << 8) |
                     (offset & 0xFC) | ((uint32)0x80000000));

  // Write out the address
  outportl(0xCF8, address);
  // Read in the data
  // (offset & 2) * 8) = 0 will choose the first word of the 32-bit register
  tmp = (uint16)((inportl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
  return tmp;
}

uint8 pciIsValid(struct PCI_BDF device) {
  if (pciConfigReadWord(device, 0) != 0xFFFF) {
    return 1;
  } else {
    return 0;
  }
}

/*return the vendor and write the device ID (if vendor was found)*/
void pci_fill_info(struct PCI_BDF *device) {
	//using hex for offset for consistency with table
  device->vendor_ID = pciConfigReadWord(*device, 0x0);
  device->device_ID = pciConfigReadWord(*device, 0x2);
  device->header_type = (uint8) (pciConfigReadWord(*device, 0xE));
}

void pciPrintInfo(struct PCI_BDF device) {

  // if the device doesent exist, just return
  if (device.device_ID == 0xFFFF)
    return;

  char str_buf[15];
  printf_str("bus % ", num_to_string(device.bus, 10, str_buf));
  printf_str("device % ", num_to_string(device.device, 10, str_buf));
  printf_str("function % ", num_to_string(device.func, 10, str_buf));

  printf_str("vendor ID: % ", num_to_string(device.vendor_ID, 16, str_buf));
  printf_str("device ID: % ", num_to_string(device.device_ID, 16, str_buf));
  printf_str("Header type: % \n", num_to_string(device.header_type, 16, str_buf));

  // otherwise check if its a multifunction device, and if it is loop through
  // all the functions
}
