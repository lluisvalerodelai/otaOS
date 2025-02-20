BITS 32       										; work in 32 bit mode

section .text
	ALIGN 4
	DD 0x1BADB002
	DD 0x00000000
	DD -(0x1BADB002 + 0x00000000)    ; set bootloader checksum

global start
extern kmain

start:
	CLI
	MOV esp, stack_space   ; set stack pointer to remaining space
	CALL kmain
	HLT

KernelHalt:      ; extra layer of protection
	CLI
	HLT
	JMP KernelHalt

section .bss  
RESB 8192        ; reserve space for the stack
stack_space:     ; we have the rest of memory for our stack
