#include "interrupt_requests.h"
#include "sys.h"
#include "vga.h"

#define SHIFT 0x2A

/*
        reference: https://wiki.osdev.org/PS/2_Keyboard for the scancode numbers
*/

struct kb_state_t {
  int shift;
  /*char[num_keys] uppercase*/
  /*char[num_keys] lowercase*/
};

struct kb_state_t kb_state = {.shift = 0};

char NONE = 0x00;
int shift = 0;

char lowercase_scan_codes[] = {
    0,   0,    '1',  '2', '3',  '4', '5', '6', '7', '8', '9', '0', '-',
    '=', 0,    0,    'q', 'w',  'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    '[', ']',  '\n', 0,   'a',  's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    ';', '\'', '`',  0,   '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',',
    '.', 0,    0,    0,   ' ',  0,   0,   0,   0,
};

char uppercase_scan_codes[] = {
    0,   0,    '!',  '"', '#',  '$', '%', '&', '/', '(', ')', '=', '_',
    '=', 0,    0,    'Q', 'W',  'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
    '[', ']',  '\n', 0,   'A',  'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
    ';', '\'', '`',  0,   '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',',
    '.', 0,    0,    0,   ' ',  0,   0,   0,   0,
};

/*get both the key pressed, and update the keyboard state*/
char get_key(char scan_code, char pressed) {

  if (scan_code == SHIFT && pressed == 0) {
    kb_state.shift = 1;
    return 0;
  } else if (scan_code == SHIFT) {
    kb_state.shift = 0;
    return 0;
  }

	if (pressed != 0) {
		return 0;
	}

  if (kb_state.shift) {
    return uppercase_scan_codes[(int)scan_code];
  } else {
    return lowercase_scan_codes[(int)scan_code];
  }
}

void keyboard_handler(struct regs *r) {
  char scan_code =
      inportb(0x60) & 0x7F; // Read from keyboard data port (lower byte)
  char pressed =
      inportb(0x60) & 0x80; // Read from keyboard data port (upper byte)

  char key = get_key(scan_code, pressed);
  if (key) {
    vga_putc(key);
  }
}

void keyboard_init() { irq_install_handler(1, (void(*))keyboard_handler); }
