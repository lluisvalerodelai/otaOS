#include "format_print.h"
#include "types.h"
#include "vga.h"

/*
 * printf but for one string only
 * since you cant do different types, you specify where you want the string with
 * just a % NOTE: max size of both combined strings is 512 bytes only
 * */
uint8 printf_str(const char *str, char *ext) {
  char new_str_buffer[512]; // print buffer

  // loop through and find the %
  int buf_i = 0;
  int str_i = 0;
  int ext_i = 0;

  while (str[str_i] != '\0') {

    if (str[str_i] == '%') {
      while (ext[ext_i] != '\0') {
        if (buf_i >= 512) {
          return 1;
        }

        new_str_buffer[buf_i] = ext[ext_i];
        buf_i++;
        ext_i++;
      }
    } else {
      new_str_buffer[buf_i] = str[str_i];
      if (buf_i >= 512) {
        return 1;
      }
      buf_i++;
    }

    str_i++; // do this no matter what we hit, so if we hit % we skip it
  }

  new_str_buffer[buf_i] = '\0';

  vga_print(new_str_buffer);
  return 0;
}

char *num_to_string(int num, uint8 base, char *str_buf) {

  if (num == 0) {
    return "0";
  }

  uint8 buf_i = 0;
  uint8 num_i = 0;
  char num_buf[15];

	if (base == 16) {
		str_buf[buf_i++] = '0';
		str_buf[buf_i++] = 'x';
	}

  if (num < 0) {
    str_buf[buf_i++] = '-';
    num = -num;
  }
  char num_c;
  while (num > 0) {
    if (num_i > 15) {
      break;
    }
    int last_digit = num % base;
		num_c = (last_digit < 10) ? ('0' + last_digit) : ('A' + last_digit - 10); //fine
		num_buf[num_i++] = num_c;
		num = num / base;
  }

  for (int i = num_i - 1; i >= 0; i--) {
    if (buf_i > 15) {
      break;
    }
    str_buf[buf_i++] = num_buf[i];
  }

  str_buf[buf_i] = '\0';
  return str_buf;
}
