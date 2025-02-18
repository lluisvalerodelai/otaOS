CC = gcc
CFLAGS = -c -Wall -m64 -Og -nostdinc -ffreestanding
LD = gcc
LDFLAGS = -nostdlib -Wl,-n,-T,link.ld -no-pie
RM = rm -fr

OBJS = boot.o mb2.o kmain.o
OBJS_P = $(addprefix build/, $(OBJS))
KERNEL = kmain.elf

build: $(OBJS) link.ld
	$(LD) $(LDFLAGS) -o build/$(KERNEL) $(OBJS_P)
	mkdir -p isofiles/boot/grub
	cp build/$(KERNEL) isofiles/boot/
	cp grub.cfg isofiles/boot/grub
	grub-mkrescue -o iso.img isofiles

run:
	qemu-system-x86_64 -no-reboot -drive format=raw,file=iso.img

clean:
	$(RM) build isofiles iso.img

.c.o:
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$@ $<

.S.o:
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$@ $<
