CFLAGS = -m32 -fno-stack-protector -fno-builtin -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-pie
AFLAGS = -f elf32
LFLAGS = -m elf_i386

BOOT_OBJS = boot.o
BOOT_TARGETS = $(addprefix build/boot/, $(BOOT_OBJS))

KERNEL_OBJS = \
							sys.o vga.o \
							global_descriptor_table.o \
							interrupt_descriptor_table.o \
							interrupt_service_routines_setup.o \
							interrupt_requests.o \
							timer.o \
							keyboard_utils.o \
							keyboard.o \
							peripheral_component_interconnect.o \
							kernel.o

KERNEL_TARGETS = $(addprefix build/kernel/, $(KERNEL_OBJS))

LINK_OBJS = $(BOOT_TARGETS) $(KERNEL_TARGETS)

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
	qemu-system-i386 -drive file=kernel.iso,format=raw 

clean:
	rm -rf build kernel.iso otaOS
