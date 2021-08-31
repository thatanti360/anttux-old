;https://www.linuxjournal.com/content/what-does-it-take-make-kernel-0

; bits 32

%include "gdt.asm"

section .multiboot               ;according to multiboot spec
        dd 0x1BADB002            ;set magic number for
                                 ;bootloader
        dd 0x0                   ;set flags
        dd - (0x1BADB002 + 0x0)  ;set checksum

section .text
global start
extern kernel_entry                      ;defined in the C file
extern handle_keyboard_interrupt

global start
global print_char_with_asm
global load_gdt
global load_idt
global keyboard_handler
global ioport_in
global ioport_out
global enable_interrupts
global detect_v86

extern main			; Defined in kernel.c
extern handle_keyboard_interrupt

detect_v86:
   smsw    ax
   and     eax,1           ;CR0.PE bit
   ret

load_gdt:
	lgdt [gdt_descriptor] ; from gdt.asm
	ret

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	ret

enable_interrupts:
	sti
	ret

keyboard_handler:
	pushad
	cld
	call handle_keyboard_interrupt
	popad
	iretd

ioport_in:
	mov edx, [esp + 4] ; PORT_TO_READ, 16 bits
	; dx is lower 16 bits of edx. al is lower 8 bits of eax
	; Format: in <DESTINATION_REGISTER>, <PORT_TO_READ>
	in al, dx					 ; Read from port DX. Store value in AL
	; Return will send back the value in eax
	; (al in this case since return type is char, 8 bits)
	ret

ioport_out:
	mov edx, [esp + 4]	; port to write; DST_IO_PORT. 16 bits
	mov eax, [esp + 8] 	; value to write. 8 bits
	; Format: out <DST_IO_PORT>, <VALUE_TO_WRITE>
	out dx, al
	ret

print_char_with_asm:
	; OFFSET = (ROW * 80) + COL
	mov eax, [esp + 8] 		; eax = row
	mov edx, 80						; 80 (number of cols per row)
	mul edx								; now eax = row * 80
	add eax, [esp + 12] 	; now eax = row * 80 + col
	mov edx, 2						; * 2 because 2 bytes per char on screen
	mul edx
	mov edx, 0xb8000			; vid mem start in edx
	add edx, eax					; Add our calculated offset
	mov eax, [esp + 4] 		; char c
	mov [edx], al
	ret

start:
	lgdt [gdt_descriptor]
	jmp CODE_SEG:.setcs       ; Set CS to our 32-bit flat code selector
	.setcs:
	mov ax, DATA_SEG          ; Setup the segment registers with our flat data selector
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, stack_space

    cli                      ;block interrupts
    mov esp, stack_space     ;set stack pointer
    call kernel_entry
    hlt                      ;halt the CPU

abtl_string: db "Greetings from the Anttux BootLoader! Launching...",0

section .bss
resb 8192                        ;8KB for stack
stack_space:



