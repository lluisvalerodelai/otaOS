#ifndef _VGA_H
#define _VGA_H

/*TODO: put return codes indicating success/failure of function execution*/
void vga_print(const char* str);
void vga_putc(const char c); 
void reset();
void scroll();
void newline();
void vga_test();

#endif // !_VGA_H

