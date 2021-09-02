#ANTTUX COMPILE.SH BASH SCRIPT
#2021, ANTI


#Opens clean.sh to delete iso folder, object files and iso
CLEAN() {
        echo "Cleaning..."
        ./clean.sh
}
#Same thing as CLEAN() except it doesn't delete the iso
CLEAN_NOISO() {
	echo "Cleaning..."
	./clean_noiso.sh
}
#Call if C error
C_COMPILER_ERROR() {
	echo "$(tput setaf 1)Build failed! (what failed: $(tput setaf 3)C$(tput setaf 1))$(tput sgr 0)"
	CLEAN
	exit 1
}
#Call if assembler error
ASM_COMPILER_ERROR() {
	echo "$(tput setaf 1)Build failed! (what failed: $(tput setaf 3)assembler$(tput setaf 1))$(tput sgr 0)"
	CLEAN
        exit 2
}
#Call if linker error
LINKER_ERROR() {
	echo "$(tput setaf 1)Linker error!$(tput sgr 0)"
	CLEAN
    exit 3
}
#Call if kernel is not x86 multiboot
ERROR_KERNEL_NOT_MULTIBOOT(){
	echo "$(tput setaf 1)file is not x86 multiboot!!$(tput sgr 0)"
	exit 4
}

CLEAN
echo "Assembling..."
#Assembles the .s file containing the bootloader
nasm -f elf32 boot.asm -o boot.o
#if as returns different than 0?
if [ $? -ne 0 ]
then
    #if yes, goto ASM_COMPILER_ERROR
    ASM_COMPILER_ERROR
fi
echo "Done"
echo "Compiling C..."
#Compiles the kernel.c file, containing the kernel
#gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
#if gcc returns different than 0?
if [ $? -ne 0 ]
then
    #if yes, goto C_COMPILER_ERROR
    C_COMPILER_ERROR
fi
echo "Done"
echo "Linking..."
#Links the Kernel with the Bootloader (MOST IMPORTANT)
ld -m elf_i386 -T linker.ld kernel.o boot.o -o kernel -nostdlib
#if ld returns different than 0?
if [ $? -ne 0 ]
then
    #if yes, goto LINKER_ERROR
    LINKER_ERROR
fi
#Checks if the final file is x86 multiboot
grub-file --is-x86-multiboot kernel
#grub-file returns different than 0?
if [ $? -ne 0 ]
then
    #if yes, goto ERROR_KERNEL_NOT_MULTIBOOT
    ERROR_KERNEL_NOT_MULTIBOOT
fi
echo "Done"
echo "Making ISO file..."
#Creates the following folders (iso/boot/grub)
mkdir -p iso/boot/grub
#Copies kernel to iso/boot
cp kernel iso/boot/
#Copies the GNU's Not Unix Grand UNified Bootloader(lol) configuration file to iso/boot/grub
cp grub.cfg iso/boot/grub/
#echo "ISO name..."
#Asks the user for the iso name
#read isoname
#Create iso
#grub-mkrescue -o $isoname.iso iso/
grub-mkrescue -o test.iso iso/
#echo "Done! ISO named $isoname has successfully been created."
CLEAN_NOISO
echo "OK"
#qemu-system-x86_64 $isoname.iso
qemu-system-x86_64 test.iso -soundhw pcspk
echo "END"
exit 0
