CFLAGS = -m32 -fno-stack-protector -fno-builtin
AFLAGS = -f elf32
LFLAGS = -m elf_i386

OBJS = boot.o kernel.o vga.o
B_OBJS = $(addprefix build/, $(OBJS))

build: $(OBJS) linker.ld
	ld $(LFLAGS) -T linker.ld -o build/kernel $(B_OBJS)
	mkdir -p otaOS/boot/grub
	cp build/kernel otaOS/boot
	cp grub.cfg otaOS/boot/grub
	grub-mkrescue -o kernel.iso otaOS/
	
run:
	qemu-system-i386 kernel.iso

clean:
	rm -rf build kernel.iso

%.o : %.c
	mkdir -p build
	gcc $(CFLAGS) -c $< -o build/$@
%.o : %.s
	mkdir -p build
	nasm $(AFLAGS) $< -o build/$@
