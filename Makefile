CFLAGS = -m32 -fno-stack-protector -fno-builtin -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-pie
AFLAGS = -f elf32
LFLAGS = -m elf_i386

OBJS = boot.o kernel.o
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
	rm -rf build kernel.iso otaOS

%.o : %.c
	mkdir -p build
	gcc $(CFLAGS) -c $< -o build/$@
%.o : %.asm
	mkdir -p build
	nasm $(AFLAGS) $< -o build/$@
