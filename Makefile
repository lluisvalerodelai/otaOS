CFLAGS = -m32 -fno-stack-protector -fno-builtin -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-pie
AFLAGS = -f elf32
LFLAGS = -m elf_i386

BOOT_SRC = boot
BOOT_BUILD = build/boot/boot.o
BOOT_OBJ = boot/boot.asm

KERNEL_SRC = kernel
KERNEL_OBJ = kernel/kernel.c kernel/vga.c

LINK_OBJS = build/boot/boot.o build/kernel/kernel.o build/kernel/vga.o

build/boot/%.o: boot/%.asm
	mkdir -p build/boot
	nasm $(AFLAGS) $< -o $@

build/kernel/%.o: kernel/%.c
	mkdir -p build/kernel
	gcc $(CFLAGS) -c $< -o $@

build: $(LINK_OBJS) linker.ld
	ld $(LFLAGS) -T linker.ld -o build/kernel_exe $(LINK_OBJS)
	mkdir -p otaOS/boot/grub
	cp build/kernel_exe otaOS/boot
	cp grub.cfg otaOS/boot/grub
	grub-mkrescue -o kernel.iso otaOS/
	
run:
	qemu-system-i386 kernel.iso

clean:
	rm -rf build kernel.iso otaOS
