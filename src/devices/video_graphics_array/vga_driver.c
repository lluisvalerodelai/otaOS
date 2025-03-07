#include "vga_driver.h"
#include "sys.h"
#include "types.h"
#include "vga.h"

vga_port misc_port = 0x3C2;
vga_port crtc_index_port = 0x3D4;
vga_port crtc_data_port = 0x3D5;
vga_port sequencer_index_port = 0x3C4;
vga_port sequencer_data_port = 0x3C5;
vga_port graphics_controller_index_port = 0x3CE;
vga_port graphics_controller_data_port = 0x3CF;
vga_port attribute_controller_index_port = 0x3C0;
vga_port attribute_controller_read_port = 0x3C1;
vga_port attribute_controller_write_port = 0x3C0;
vga_port attribute_controller_reset_port = 0x3dA;

/*returns 1 if yes*/
uint8 supports_mode(uint32 width, uint32 height, uint32 colorDepth) {
  // only supported mode for now because I have a life
  return width == 320 && height == 200 && colorDepth == 8;
}

//OK, SO,
//INVALID OPCODE EXCPETIONS
//THEY ARE HAPPENING BECAUSE IM OVERFLOWING MY OWN KERNELS ALLOCATED STACK PROB
void write_registers(uint8 *registers) {
  // write to misc port
  outportb(misc_port, *(registers++));

  // seq port
  for (uint8 i = 0; i < 5; i++) {
    outportb(sequencer_index_port, i); // first write the index to index port
    outportb(sequencer_data_port, *(registers++));
  }

  // calm luh rawdogged mutex
  outportb(crtc_index_port, 0x03);
  outportb(crtc_data_port, inportb(crtc_data_port) | 0x80);
  outportb(crtc_index_port, 0x11);
  outportb(crtc_data_port, inportb(crtc_data_port) & ~0x80);

  // for making sure we dont overwrite the locked condition
  registers[0x03] = registers[0x03] | 0x80;
  registers[0x11] = registers[0x11] & ~0x80;

  for (uint8 i = 0; i < 25; i++) {
    outportb(crtc_index_port, i);
    outportb(crtc_data_port, *(registers++));
  }

  for (uint8 i = 0; i < 9; i++) {
    outportb(graphics_controller_index_port, i);
    outportb(graphics_controller_data_port, *(registers++));
  }

  for (uint8 i = 0; i < 21; i++) {
    inportb(attribute_controller_reset_port); // reset it
    outportb(attribute_controller_index_port, i);
    outportb(attribute_controller_write_port, *(registers++));
  }
  inportb(attribute_controller_reset_port);
  outportb(attribute_controller_index_port, 0x20);
}

uint8 g_320x200x256[] = {/* MISC */
                         0x63,
                         /* SEQ */
                         0x03, 0x01, 0x0F, 0x00, 0x0E,
                         /* CRTC */
                         0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00,
                         0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 0x0E,
                         0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3, 0xFF,
                         /* GC */
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
                         /* AC */
                         0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                         0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00,
                         0x0F, 0x00, 0x00};

/* returns 1 on success, 0 on failure*/
uint8 set_mode(uint32 width, uint32 height, uint32 colorDepth) {

  if (!supports_mode(width, height, colorDepth)) {
    return 0;
  }

  write_registers(g_320x200x256);
  return 1;
}

uint16 *get_frame_buffer_segment() {
  outportb(graphics_controller_index_port, 0x06);
  uint8 segment_num = (inportb(graphics_controller_data_port) >> 2) & 0x03;

  switch (segment_num) {
  case 0:
    return (uint16 *)0x00000; // this could be what breaks
  case 1:
    return (uint16 *)0xA0000;
  case 2:
    return (uint16 *)0xB0000;
  case 3:
    return (uint16 *)0xB8000;
  }
}

void _put_pixel(uint32 x, uint32 y, uint8 color_index) {
  uint16 *pixel_addr = get_frame_buffer_segment() + (320 * y + x);
  *(pixel_addr) = color_index;
}

// NOTE: this might be what breaks, seems to be VM specific
uint8 get_color_index(uint8 r, uint8 g, uint8 b) {
  if (r == 0x00 && g == 0x00 && b == 0xA8) {
    return 0x01;
  }
}

void put_pixel(uint32 x, uint32 y, uint8 r, uint8 g, uint8 b) {
  _put_pixel(x, y, get_color_index(r, g, b));
}
