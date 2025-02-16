default: otaOS.iso

multiboot_header.o: multiboot_header.asm
	nasm -f elf64 multiboot_header.asm

boot.o: boot.asm
	nasm -f elf64 boot.asm

kernel.bin: multiboot_header.o boot.o
	ld -n -o kernel.bin -T linker.ld multiboot_header.o boot.o

otaOS.iso: kernel.bin
	mkdir -p isofiles/boot/grub
	cp grub.cfg isofiles/boot/grub
	cp kernel.bin isofiles/boot/
	grub-mkrescue -o os.iso isofiles

run: os.iso
	qemu-system-x86_64 -cdrom os.iso

clean:
	rm -f *.o
	rm -f *.bin
	rm -rf isofiles
	rm -f os.iso
