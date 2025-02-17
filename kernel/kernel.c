#include "types.h"

void kernelMain() {
	uint16_t *videoMemory = (uint16_t *)0xB8000; //start of vram
	const int8_t *message = "hello world!"; //8 bytes per

	for (int i = 0; message[i] != '\0'; i++) {
          videoMemory[i] = 0x01 << 8 | message[i]; 	// stepping 2 bytes at a time 
																										// high byte for style, 
																										// low byte for ascii char
        }

	while (1);
}
