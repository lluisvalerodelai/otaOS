ENTRY(_start)

SECTIONS {
  /* Start at image 1 meg */
  . = 1M;

  /* multiboot section must be first then text */
  .boot BLOCK(4K) : ALIGN(4K) {
    KEEP(*(.multiboot))
  }

  /* multiboot section must be first then text */
  .text BLOCK(4K) : ALIGN(4K) {
    *(.text)
  }

  /* Read-write data (initialized) */
  .data BLOCK(4K) : ALIGN(4K) {
    *(.data)
  }

  /* Read-write data (uninitialized) */
  .bss BLOCK(4K) : ALIGN(4K) {
    *(COMMON)
    *(.bss)
  }

  /* Stack separate */
  .stack BLOCK(4K) : ALIGN(4K) {
    *(.bootstrap_stack)
  }

  /* Other sections will be here */
}
