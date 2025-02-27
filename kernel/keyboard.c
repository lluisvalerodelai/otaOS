#include "interrupt_requests.h"
#include "keyboard_utils.h"
#include "sys.h"
#include "vga.h"

#define SHIFT 0x2A
#define CAPS_LOCK 0x3A

/*
        reference: https://wiki.osdev.org/PS/2_Keyboard for the scancode numbers
*/

/*keeps track of if shift was held down, and the caps lock setting*/
struct kb_state_t {
  int shift;
  /*char[num_keys] uppercase*/
  /*char[num_keys] lowercase*/
};

struct kb_state_t kb_state = {.shift = 0};

char NONE = 0x00;
int shift = 0;

char lowercase_scan_codes[255] = {0};
char uppercase_scan_codes[255] = {0};

int update_shift(char scan_code, char pressed) {

  // shift inverts the value of shift state when pressed/released
  // caps_lock inverts the value of shift state when pressed only

  if (scan_code == SHIFT) {
    if (kb_state.shift == 0) { // i have no bools :(
      kb_state.shift = 1;
    } else {
      kb_state.shift = 0;
    }

    return 1;
  }

  if (scan_code == CAPS_LOCK) {
    if (pressed == 0) {
      if (kb_state.shift == 0) {
        kb_state.shift = 1;
      } else {
        kb_state.shift = 0;
      }
    }

    return 1;
  }

  return 0;
}

/*get both the key pressed, and update the keyboard state*/
char get_key(char scan_code, char pressed) {

  if (update_shift(scan_code, pressed)) {
    return 0;
  }

  if (pressed != 0) { // if a key was released dont do anything
    return 0;
  }

  if (kb_state.shift) {
    return uppercase_scan_codes[scan_code];
  } else {
    return lowercase_scan_codes[scan_code];
  }

	return 0;
}

void keyboard_handler(struct regs *r) {
  // Read from keyboard data port (lower byte)
  char scan_code = inportb(0x60) & 0x7F;
  // Read from keyboard data port (upper byte)
  char pressed = inportb(0x60) & 0x80;

  char key = get_key(scan_code, pressed);

  if (key) {
    vga_putc(key);
  }
}

void keyboard_init() {
  set_lower_scan_codes(&lowercase_scan_codes[0]);
  set_upper_scan_codes(&uppercase_scan_codes[0]);
  irq_install_handler(1, (void(*))keyboard_handler);
}
