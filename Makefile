default: build

build/kernel.o: kernel.c
	mkdir -p build
	i686-elf-gcc -c kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

build/multiboot_header.o: multiboot_header.asm
	mkdir -p build
	nasm -f elf32 multiboot_header.asm -o build/multiboot_header.o

build/boot.o: boot.asm
	mkdir -p build
	nasm -f elf32 boot.asm -o build/boot.o

build/kernel.bin: build/multiboot_header.o build/boot.o build/kernel.o linker.ld
	# ld -n -o build/kernel.bin -T linker.ld build/multiboot_header.o build/boot.o build
	ld -m elf_i386 -T linker.ld -o build/kernel.bin build/multiboot_header.o build/boot.o build/kernel.o 

build/os.iso: build/kernel.bin grub.cfg
	mkdir -p build/isofiles/boot/grub
	cp grub.cfg build/isofiles/boot/grub
	cp build/kernel.bin build/isofiles/boot/
	grub-mkrescue -o build/os.iso build/isofiles

run: build/os.iso
	qemu-system-x86_64 -cdrom build/os.iso

build: build/os.iso

clean:
	rm -rf build
