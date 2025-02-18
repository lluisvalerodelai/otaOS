	.set		MAGIC, 0xE85250D6	/* Mulitboot 2 magic number */
	.set		FLAGS, 0		/* 0 is i386 protected mode */
	.set		CHECKSUM, -(MAGIC + FLAGS + (mbh_end - mbh_start))

/* The multiboot header */
	.section	.multiboot
	.align		4
mbh_start:
	.long		MAGIC
	.long		FLAGS
	.long		mbh_end - mbh_start
	.long		CHECKSUM

/* End tag */
	.word		0					// type
	.word		0					// flags
	.long		8					// size
mbh_end:

