#ifndef  _VGA_DRIVER_H
#define _VGA_DRIVER_H

#include "types.h"

typedef uint16 vga_port; // for the conveniece

uint8 set_mode(uint32 width, uint32 height, uint32 colorDepth);
void put_pixel(uint32 x, uint32 y, uint8 r, uint8 g, uint8 b);

#endif // ! __VGA_DRIVER_H
