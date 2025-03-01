#include "peripheral_component_interconnect.h"
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

uint16 pciConfigReadWord(uint8 bus, uint8 slot, uint8 func, uint8 offset) {
  uint32 address; // the address offset to get to the 256 byte region that is
                  // allocated for some specific device on the PCI
  uint32 lbus = (uint32)bus;
  uint32 lslot = (uint32)slot;
  uint32 lfunc = (uint32)func;
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

uint16 pciCheckVendor(uint8 bus, uint8 slot) {
  uint16 vendor, device;
  /* Try and read the first configuration register. Since there are no
   * vendors that == 0xFFFF, it must be a non-existent device. */

  if ((vendor = pciConfigReadWord(bus, slot, 0, 0)) != 0xFFFF) {
    device = pciConfigReadWord(bus, slot, 0, 2); // TODO: return device too xD
  }
  return (vendor);
}

