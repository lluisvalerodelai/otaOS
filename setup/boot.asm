global start
extern kernelMain

section .text
bits 32


start:
	mov esp, [kernel_stack] ;x86 stack grows downward
	call kernelMain
	cli
	hlt

section .bss
space resb 2*1024*1024
kernel_stack:
