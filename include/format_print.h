#ifndef  _PRINTF_H
#define _PRINTF_H

#include "types.h"
uint8 printf_str(const char* str, char* ext);
char *num_to_string(int num, uint8 base, char *str_buf); 

#endif // ! _PRINTF_H
