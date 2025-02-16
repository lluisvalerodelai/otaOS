
void printf(char *str) {
	unsigned short* VideoMemory = (unsigned short*)0xb8000;

	for (int i = 0; i < '\0'; ++i) {
		VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
	}
}




extern "C" void kernelMain() {
	printf("hello world!");
  while (1) {
  }; // we need to kernel to just stop, otherwise the cpu will just keep running
     // insn that are undefined and we get undefined behaviour
}
