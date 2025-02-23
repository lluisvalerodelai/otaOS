; the main entry point for the kernel,
; this is where we call main, seutp the stack, and set up GDT and interrupts

[BITS 32]
global start
start:
	mov esp, _sys_stack     ;point the stack to our new stack are
	jmp stublet

ALIGN 4
mboot:
    ; Multiboot macros to make a few lines later more readable
    MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1
    MULTIBOOT_AOUT_KLUDGE	equ 1<<16
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end
		
		; GRUB multiboot header
		dd MULTIBOOT_HEADER_MAGIC
		dd MULTIBOOT_HEADER_FLAGS
		dd MULTIBOOT_CHECKSUM

	  ; AOUT kludge - must be physical addresses
    ; The linker script fills in the data for these ones!
    dd mboot
    dd code
    dd bss
    dd end
    dd start

; endless loop for security
; we will call extern _kmain followed by call _kmain before the jump

stublet:
	extern kmain
	call kmain
	jmp $

; here we define the _gdt_flush function, which we call from C to setup the proper registers for gdt
; loading the GDT
global gdt_flush  ; C can access this as gdt_flush()
extern gp
gdt_flush:
	lgdt [gp]
	mov ax, 0x10 ; each entry is 2 bytes, the null entry is first so we need to preload the offset
	mov ds, ax ; into all the necessary registers
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2  ;0x08 is the offset to our code segment
flush2:
	ret  ;go back to the C code

; TODO add interrupt service routiunes here
global idt_load
extern idtp
idt_load:
	lidt [idtp]
	ret

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

isr0:
    cli
    push byte 0  ; dummy error code for uniform stack frame
    push byte 0  ; ISR number
    jmp isr_common_stub

isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub

isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub

isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub

isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub

isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

isr8:
    cli
    push byte 8  ; CPU exception with an error code
    jmp isr_common_stub ; interrupt 8 returns a value iself, so no need to do it here

isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

isr10:
    cli
    push byte 0  ; CPU exception with an error code
    push byte 10
    jmp isr_common_stub

isr11:
    cli
    push byte 0  ; CPU exception with an error code
    push byte 11
    jmp isr_common_stub

isr12:
    cli
    push byte 0  ; CPU exception with an error code
    push byte 12
    jmp isr_common_stub

isr13:
    cli
    push byte 0  ; CPU exception with an error code
    push byte 13
    jmp isr_common_stub

isr14:
    cli
    push byte 0  ; CPU exception with an error code
    push byte 14
    jmp isr_common_stub

isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

isr17:
    cli
    push byte 0  ; CPU exception with an error code
    push byte 17
    jmp isr_common_stub

isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub

isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub

isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub

isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub

isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub

isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub

isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub

isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub

isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub

isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub

isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub

isr30:
    cli
    push byte 0  ; CPU exception with an error code
    push byte 30
    jmp isr_common_stub

isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub

extern fault_handler

isr_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp   ; Push us the stack
	push eax
	mov eax, fault_handler
	call eax       ; A special call, preserves the 'eip' register
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8     ; Cleans up the pushed error code and pushed ISR number
	iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

; define the stack (it grows downn)
SECTION .bss
	resb 8192 ;8kb
_sys_stack:
