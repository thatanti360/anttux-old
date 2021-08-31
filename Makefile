#TODO: I don't like Makefiles

all:
	nasm -f elf32 boot.asm -o boot.o
	gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	ld -m elf_i386 -T linker.ld kernel.o boot.o -o kernel -nostdlib
	grub-mkrescue -o test.iso iso/
	mkdir -p iso/boot/grub
	cp kernel iso/boot/
	rm kernel
	rm kernel.o
	rm boot.o
	qemu-system-x86_64 test.iso -soundhw pcspk

clean:
	rm kernel
	rm kernel.o
	rm boot.o
	rm *.iso