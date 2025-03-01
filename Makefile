CFLAGS = -m32 -fno-stack-protector -fno-builtin -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-pie
AFLAGS = -f elf32
LFLAGS = -m elf_i386

INCLUDE_DIR = ./include

BOOT_OBJS = boot.o
BOOT_TARGETS = $(addprefix build/boot/, $(BOOT_OBJS))

KERNEL_OBJS = \
							sys/sys.o \
							devices/video_graphics_array/vga.o \
							global_descriptor_table.o \
							interrupts/interrupt_descriptor_table.o \
							interrupts/interrupt_service_routines_setup.o \
							interrupts/interrupt_requests.o \
							devices/timer/timer.o \
							devices/keyboard/keyboard_utils.o \
							devices/keyboard/keyboard.o \
							devices/peripheral_component_interconnect.o \
							kernel.o

KERNEL_TARGETS = $(addprefix build/, $(KERNEL_OBJS))

LINK_OBJS = $(BOOT_TARGETS) $(KERNEL_TARGETS)

build/boot/%.o: boot/%.asm
	mkdir -p build/boot
	nasm $(AFLAGS) $< -o $@

buildprep:
	mkdir -p build/interrupts #TODO: find a better way of doing this. this sucks.
	mkdir -p build/devices/keyboard #theres no need to recereate the whole src directory here
	mkdir -p build/devices/video_graphics_array #just dump all .o files in one place
	mkdir -p build/devices/timer
	mkdir -p build/sys

build/%.o: src/%.c | buildprep
	gcc $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

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
