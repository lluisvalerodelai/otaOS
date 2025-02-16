void kernelMain() {
	char *videoMemory = (char *)0xB8000; //start of vram
	const char *message = "hello world!";

	for (int i = 0; message[i] != '\0'; i++) {
		videoMemory[i * 2] = message[i];
		videoMemory[i * 2 + 1] = 0x01;
	}

	while (1);
}
