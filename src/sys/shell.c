#include "shell.h"
#include "vga.h"

void render_prompt() {
	vga_print(">");
}

void shell_init() {
	reset();	
	render_prompt();
}
