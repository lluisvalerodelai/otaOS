ENTRY(start)

SECTIONS {
	. = 1M;

	/* .boot : */
	/* { */
	/* } */

	.text :
	{
		*(.multiboot_header)
		*(.text)
	}

	.rodata :
	{
		*(.rodata)
	}

	.data : 
	{
		*(.data)
	}

	.bss :
	{
		*(COMMON)
		*(.bss)
	}
}
