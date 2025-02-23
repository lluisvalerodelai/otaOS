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

; define the stack (it grows downn)
SECTION .bss
	resb 8192 ;8kb
_sys_stack:
