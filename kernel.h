//let's see how GNU nano is...
//it's cool

#define ANTTUX_VERSION "Anttux r2 v6.0k4"


#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef uint32 size_t;

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

uint16* vga_buffer;

#define NULL 0

#define KBRD_INTRFC 0x64
 
/* keyboard interface bits */
#define KBRD_BIT_KDATA 0 /* keyboard data is in buffer (output buffer is empty) (bit 0) */
#define KBRD_BIT_UDATA 1 /* user data is in buffer (command buffer is empty) (bit 1) */
 
#define KBRD_IO 0x60 /* keyboard IO port */
#define KBRD_RESET 0xFE /* reset CPU command */
 
#define bit(n) (1<<(n)) /* Set bit n to 1 */
 
/* Check if bit n in flags is set */
#define check_flag(flags, n) ((flags) & bit(n))

// not quite a string but it works lol
#define string char *

typedef enum { false, true } bool;

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    PURPLE,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

enum {
    CPUID_FEAT_ECX_SSE3         = 1 << 0, 
    CPUID_FEAT_ECX_PCLMUL       = 1 << 1,
    CPUID_FEAT_ECX_DTES64       = 1 << 2,
    CPUID_FEAT_ECX_MONITOR      = 1 << 3,  
    CPUID_FEAT_ECX_DS_CPL       = 1 << 4,  
    CPUID_FEAT_ECX_VMX          = 1 << 5,  
    CPUID_FEAT_ECX_SMX          = 1 << 6,  
    CPUID_FEAT_ECX_EST          = 1 << 7,  
    CPUID_FEAT_ECX_TM2          = 1 << 8,  
    CPUID_FEAT_ECX_SSSE3        = 1 << 9,  
    CPUID_FEAT_ECX_CID          = 1 << 10,
    CPUID_FEAT_ECX_FMA          = 1 << 12,
    CPUID_FEAT_ECX_CX16         = 1 << 13, 
    CPUID_FEAT_ECX_ETPRD        = 1 << 14, 
    CPUID_FEAT_ECX_PDCM         = 1 << 15, 
    CPUID_FEAT_ECX_PCIDE        = 1 << 17, 
    CPUID_FEAT_ECX_DCA          = 1 << 18, 
    CPUID_FEAT_ECX_SSE4_1       = 1 << 19, 
    CPUID_FEAT_ECX_SSE4_2       = 1 << 20, 
    CPUID_FEAT_ECX_x2APIC       = 1 << 21, 
    CPUID_FEAT_ECX_MOVBE        = 1 << 22, 
    CPUID_FEAT_ECX_POPCNT       = 1 << 23, 
    CPUID_FEAT_ECX_AES          = 1 << 25, 
    CPUID_FEAT_ECX_XSAVE        = 1 << 26, 
    CPUID_FEAT_ECX_OSXSAVE      = 1 << 27, 
    CPUID_FEAT_ECX_AVX          = 1 << 28,
 
    CPUID_FEAT_EDX_FPU          = 1 << 0,  
    CPUID_FEAT_EDX_VME          = 1 << 1,  
    CPUID_FEAT_EDX_DE           = 1 << 2,  
    CPUID_FEAT_EDX_PSE          = 1 << 3,  
    CPUID_FEAT_EDX_TSC          = 1 << 4,  
    CPUID_FEAT_EDX_MSR          = 1 << 5,  
    CPUID_FEAT_EDX_PAE          = 1 << 6,  
    CPUID_FEAT_EDX_MCE          = 1 << 7,  
    CPUID_FEAT_EDX_CX8          = 1 << 8,  
    CPUID_FEAT_EDX_APIC         = 1 << 9,  
    CPUID_FEAT_EDX_SEP          = 1 << 11, 
    CPUID_FEAT_EDX_MTRR         = 1 << 12, 
    CPUID_FEAT_EDX_PGE          = 1 << 13, 
    CPUID_FEAT_EDX_MCA          = 1 << 14, 
    CPUID_FEAT_EDX_CMOV         = 1 << 15, 
    CPUID_FEAT_EDX_PAT          = 1 << 16, 
    CPUID_FEAT_EDX_PSE36        = 1 << 17, 
    CPUID_FEAT_EDX_PSN          = 1 << 18, 
    CPUID_FEAT_EDX_CLF          = 1 << 19, 
    CPUID_FEAT_EDX_DTES         = 1 << 21, 
    CPUID_FEAT_EDX_ACPI         = 1 << 22, 
    CPUID_FEAT_EDX_MMX          = 1 << 23, 
    CPUID_FEAT_EDX_FXSR         = 1 << 24, 
    CPUID_FEAT_EDX_SSE          = 1 << 25, 
    CPUID_FEAT_EDX_SSE2         = 1 << 26, 
    CPUID_FEAT_EDX_SS           = 1 << 27, 
    CPUID_FEAT_EDX_HTT          = 1 << 28, 
    CPUID_FEAT_EDX_TM1          = 1 << 29, 
    CPUID_FEAT_EDX_IA64         = 1 << 30,
    CPUID_FEAT_EDX_PBE          = 1 << 31
};

void CLI()
{
	asm volatile("cli");
}

#define VIDMEM 0xb8000
#define ROWS 25
#define COLS 80
#define COMMAND_BUFFER_SIZE 100
#define IDT_SIZE 256
#define KERNEL_CODE_SEGMENT_OFFSET 0x8
#define IDT_INTERRUPT_GATE_32BIT 0x8e
#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define PROMPT "anttux>"
#define PROMPT_LENGTH 8

#include "keyboard_map.h"

void printchar(char c, int row, int col) {
	// OFFSET = (ROW * 80) + COL
	char* offset = (char*) (VIDMEM + 2*((row * COLS) + col));
	*offset = c;
}

extern void load_gdt();
extern void keyboard_handler();
extern char ioport_in(unsigned short port);
extern void ioport_out(unsigned short port, unsigned char data);
extern void load_idt(unsigned int* idt_address);
extern void enable_interrupts();

struct IDT_pointer {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));
struct IDT_entry {
	unsigned short offset_lowerbits; // 16 bits
	unsigned short selector; // 16 bits
	unsigned char zero; // 8 bits
	unsigned char type_attr; // 8 bits
	unsigned short offset_upperbits; // 16 bits
} __attribute__((packed));

struct IDT_entry IDT[IDT_SIZE];

int cursor_pos = 0;
int cursor_row = 0;
int cursor_col = 0;

char command_buffer[COMMAND_BUFFER_SIZE];
int command_len = 0;

extern void print_char_with_asm(char c, int row, int col);

bool streq(char* string1, int str1len, char* string2, int str2len) {
	if (str1len != str2len) return false;
	for (int i = 0; i < str1len; i++) {
		if (string1[i] != string2[i]) return false;
	}
	return true;
}

void print_prompt() {
	cursor_col = 0;
	print(PROMPT);
	cursor_col = PROMPT_LENGTH;
}

static inline void outb(uint16 port, uint8 data) {
    asm("outb %1, %0" : : "dN" (port), "a" (data));
}

static inline uint8 inb(uint16 port) {
    uint8 r;
    asm("inb %1, %0" : "=a" (r) : "dN" (port));
    return r;
}

static inline uint16 inw(uint16 port) {
    uint16 r;
    asm("inw %1, %0" : "=a" (r) : "dN" (port));
    return r;
}

static inline void outw(uint16 port, uint16 data) {
    asm("outw %1, %0" : : "dN" (port), "a" (data));
}

void init_idt() {
	// Get the address of the keyboard_handler code in kernel.asm as a number
	unsigned int offset = (unsigned int)keyboard_handler;
	// Populate the first entry of the IDT
	// TODO why 0x21 and not 0x0?
	// My guess: 0x0 to 0x2 are reserved for CPU, so we use the first avail
	IDT[0x21].offset_lowerbits = offset & 0x0000FFFF; // lower 16 bits
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = IDT_INTERRUPT_GATE_32BIT;
	IDT[0x21].offset_upperbits = (offset & 0xFFFF0000) >> 16;
	// Program the PICs - Programmable Interrupt Controllers
	// Background:
		// In modern architectures, the PIC is not a separate chip.
		// It is emulated in the CPU for backwards compatability.
		// The APIC (Advanced Programmable Interrupt Controller)
		// is the new version of the PIC that is integrated into the CPU.
		// Default vector offset for PIC is 8
		// This maps IRQ0 to interrupt 8, IRQ1 to interrupt 9, etc.
		// This is a problem. The CPU reserves the first 32 interrupts for
		// CPU exceptions such as divide by 0, etc.
		// In programming the PICs, we move this offset to 0x2 (32) so that
		// we can handle all interrupts coming to the PICs without overlapping
		// with any CPU exceptions.

	// Send ICWs - Initialization Command Words
	// PIC1: IO Port 0x20 (command), 0xA0 (data)
	// PIC2: IO Port 0x21 (command), 0xA1 (data)
	// ICW1: Initialization command
	// Send a fixed value of 0x11 to each PIC to tell it to expect ICW2-4
	// Restart PIC1
	ioport_out(PIC1_COMMAND_PORT, 0x11);
	ioport_out(PIC2_COMMAND_PORT, 0x11);
	// ICW2: Vector Offset (this is what we are fixing)
	// Start PIC1 at 32 (0x20 in hex) (IRQ0=0x20, ..., IRQ7=0x27)
	// Start PIC2 right after, at 40 (0x28 in hex)
	ioport_out(PIC1_DATA_PORT, 0x20);
	ioport_out(PIC2_DATA_PORT, 0x28);
	// ICW3: Cascading (how master/slave PICs are wired/daisy chained)
	// Tell PIC1 there is a slave PIC at IRQ2 (why 4? don't ask me - https://wiki.osdev.org/8259_PIC)
	// Tell PIC2 "its cascade identity" - again, I'm shaky on this concept. More resources in notes
	ioport_out(PIC1_DATA_PORT, 0x0);
	ioport_out(PIC2_DATA_PORT, 0x0);
	// ICW4: "Gives additional information about the environemnt"
	// See notes for some potential values
	// We are using 8086/8088 (MCS-80/85) mode
	// Not sure if that's relevant, but there it is.
	// Other modes appear to be special slave/master configurations (see wiki)
	ioport_out(PIC1_DATA_PORT, 0x1);
	ioport_out(PIC2_DATA_PORT, 0x1);
	// Voila! PICs are initialized

	// Mask all interrupts (why? not entirely sure)
	// 0xff is 16 bits that are all 1.
	// This masks each of the 16 interrupts for that PIC.
	ioport_out(PIC1_DATA_PORT, 0xff);
	ioport_out(PIC2_DATA_PORT, 0xff);

	// Last but not least, we fill out the IDT descriptor
	// and load it into the IDTR register of the CPU,
	// which is all we need to do to make it active.
	struct IDT_pointer idt_ptr;
	idt_ptr.limit = (sizeof(struct IDT_entry) * IDT_SIZE) - 1;
	idt_ptr.base = (unsigned int) &IDT;
	// Now load this IDT
	load_idt(&idt_ptr);
}

void kb_init() {
	// 0xFD = 1111 1101 in binary. enables only IRQ1
	// Why IRQ1? Remember, IRQ0 exists, it's 0-based
	ioport_out(PIC1_DATA_PORT, 0xFD);
}

// bool playsounds = true;
// bool playerchar = false;
// int spin = 1;

bool ShiftLock = false;

void handle_keyboard_interrupt() {
	SetCursorPosition(PositionFromCoords(cursor_col,cursor_row+1));
	// Write end of interrupt (EOI)
	ioport_out(PIC1_COMMAND_PORT, 0x20);

	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
	// Lowest bit of status will be set if buffer not empty
	// (thanks mkeykernel)
	if (status & 0x1) {
		char keycode = ioport_in(KEYBOARD_DATA_PORT);
		if (keycode < 0 || keycode >= 128) return;
		if (keycode != 72 || keycode != 80 || keycode != 75 || keycode != 77)
		{
		switch (keycode)
		{
		case 72:
			cursor_row--;
			break;
		case 80:
			cursor_row++;
			break;
		case 75:
			cursor_col--;
			break;
		case 77:
			cursor_col++;
			break;
		}
		}
		if(keycode == 71)
		{
			aybabtu();
		}
		if(keycode == 1)
		{
			reboot();
		}
		if(keycode == 58)
		{
			if (ShiftLock == true)
			{
				ShiftLock = false;
				while(inb(0x64) & 0x2);
                		outb(0x60, 0xed);
		                outb(0x60, 4);
			} else {
				ShiftLock = true;
				while(inb(0x64) & 0x2);
                		outb(0x60, 0xed);
		                outb(0x60, 4);
			}
		}
			// if (keycode == 17)
			// {
			// 	//W
			// 	player_move_up(1);
			// 	if(playsounds)
			// 	{
			// 		play_sound(300,25);				
			// 	}
			// }
			// if (keycode == 30)
			// {
			// 	//A
			// 	player_move_left(2);
			// 	if(playsounds)
			// 	{
			// 		play_sound(300,25);				
			// 	}
			// }
			// if (keycode == 31)
			// {
			// 	//S
			// 	player_move_down(1);
			// 	if(playsounds)
			// 	{
			// 		play_sound(300,25);				
			// 	}
			// }
			// if (keycode == 32)
			// {
			// 	//D
			// 	player_move_right(2);
			// 	if(playsounds)
			// 	{
			// 		play_sound(300,25);				
			// 	}
			// }
			// if (keycode == 15)
			// {
			// 	int index = 0;
			// 	for(int i = 0; i < 201; i++)
			// 	{
			// 		sleep(25);
			// 		print_char_color('A' + index,BRIGHT_RED);
			// 		print_int(index);
			// 		index++;
			// 	}	
			// }
			// if (keycode == 2)
			// {
			// 	init_vga(WHITE,BLUE);
			// 	player_update_pos();
			// }
			// if (keycode == 3)
			// {
			// 	init_vga(BROWN,GREEN);
			// 	player_update_pos();
			// }
			// if (keycode == 4)
			// {
			// 	init_vga(BRIGHT_BLUE,BLACK);
			// 	player_update_pos();
			// }
			// if (keycode == 5)
			// {
			// 	init_vga(WHITE,BLACK);
			// 	player_update_pos();
			// }
			// if (keycode == 6)
			// {
			// 	init_vga(BRIGHT_CYAN,BRIGHT_MAGENTA);
			// 	player_update_pos();
			// }
			// if (keycode == 7)
			// {
			// 	for (int i = 0; i < 5; i++)
			// 	{
			// 		if (playsounds)
			// 		{
			// 			play_sound(50,250);	
			// 			player_move_up(spin);
			// 			play_sound(100,250);	
			// 			player_move_right(spin);
			// 			play_sound(150,250);	
			// 			player_move_down(spin);
			// 			play_sound(200,250);	
			// 			player_move_left(spin);
			// 		} else {
			// 			sleep(250);
			// 			player_move_up(spin);
			// 			sleep(250);
			// 			player_move_right(spin);
			// 			sleep(250);
			// 			player_move_down(spin);
			// 			sleep(250);
			// 			player_move_left(spin);
			// 		}
			// 	}
			// 	spin++;
			// }
			// if (keycode == 11)
			// {
			// 	if (playsounds == true)
			// 	{
			// 		playsounds = false;
			// 		print_ra("Disabled sounds.");
			// 	} else {
			// 		playsounds = true;
			// 		print_ra("Enabled sounds. ");
			// 	}
			// }
			// if (keycode == 16)
			// {
			// 	keyboard_case == 1;
			// }
			if (keycode == 28) {
			// ENTER : Newline
			cursor_row++;
			//newline();
			play_sound(500,10);
			cursor_col = 0;
			// // Handle command
			// if (streq(command_buffer, command_len, "shutdown", 8)) {
			// 	shutdown_vm();
			// }
            // } else if (streq(command_buffer, command_len, "restart", 7)){
            //     reboot();
            // } else if (streq(command_buffer, command_len, "halt", 4)) {
            //     halt(1);
            // } else if (streq(command_buffer, command_len, "beep", 4)) {
            //     play_sound(500,500);
            // } else if (streq(command_buffer, command_len, "randomnumber", 12)) {
            //     newline();
            //     int x = rand_r(420);
            //     print_int(x);
            //     cursor_row++;
			// 	newline();
			// } else if (streq(command_buffer, command_len, "clear", 5)) {
			// 	clear_screen();
			// 	cursor_row = 0;
			// } else if (streq(command_buffer, command_len, "exit", 4)) {
			// 	return;		
			// } else if (streq(command_buffer, command_len, "cli", 3)) {
			// 	CLI();
			// 	newline();
			// 	print("cli");
			// 	cursor_row += 1;			
			// } else if (command_len < 1) {
			// 	// do nothing
			// } else {
			// 	play_sound(200,30);
			// 	print("Command not found: ");
			// 	print(command_buffer);
			// 	newline();
			// 	cursor_row++;
			// }
			// command_len = 0;
            // command_buffer[0];
		} else if (keycode == 14) {
			// BACKSPACE: Move back one unless on prompt
			// if (cursor_col > PROMPT_LENGTH) {
				print_char_with_asm(' ', cursor_row, --cursor_col);
				play_sound(900,10);
			// }
		} else {
			//if (command_len >= COMMAND_BUFFER_SIZE) return;
			//command_buffer[command_len++] = keyboard_map[keycode];
			if(keycode != 58)
			{
				switch (ShiftLock)
				{
					case true:
						switch ((keyboard_map[keycode]))
						{
							case '1':
								printchar('!', cursor_row, cursor_col++);
								break;
							
							case '2':
								printchar('@', cursor_row, cursor_col++);
								break;

							case '3':
								printchar('#', cursor_row, cursor_col++);
								break;

							case '4':
								printchar('$', cursor_row, cursor_col++);
								break;
							
							case '5':
								printchar('%', cursor_row, cursor_col++);
								break;

							case '6':
								printchar('^', cursor_row, cursor_col++);
								break;
							
							case '7':
								printchar('&', cursor_row, cursor_col++);
								break;
							
							case '8':
								printchar('*', cursor_row, cursor_col++);
								break;

							case '9':
								printchar('(', cursor_row, cursor_col++);
								break;

							case '0':
								printchar(')', cursor_row, cursor_col++);
								break;

							case '-':
								printchar('_', cursor_row, cursor_col++);
								break;

							case '=':
								printchar('+', cursor_row, cursor_col++);
								break;

							case ',':
								printchar('<', cursor_row, cursor_col++);
								break;

							case '.':
								printchar('>', cursor_row, cursor_col++);
								break;

							case '/':
								printchar('?', cursor_row, cursor_col++);
								break;

							case '[':
								printchar('{', cursor_row, cursor_col++);
								break;

							case ']':
								printchar('}', cursor_row, cursor_col++);
								break;

							case ';':
								printchar(':', cursor_row, cursor_col++);
								break;

							// case "'":
							// 	printchar('"', cursor_row, cursor_col++);
							// 	break;

							// case "\":
							// 	printchar('|', cursor_row, cursor_col++);
							// 	break;
							
							default:
								if(keycode != 72 || keycode != 80 || keycode != 75 || keycode != 77)
								{
									printchar(keyboard_map[keycode] - 32, cursor_row, cursor_col++);
								}
								break;
						}
						break;
					case false:
						if(keycode != 72 || keycode != 80 || keycode != 75 || keycode != 77)
						{
							printchar(keyboard_map[keycode], cursor_row, cursor_col++);
						}
						break;
				}	
			}
			// print_int(keycode);
			play_sound(800,5);
			if (cursor_col >= COLS) {
				cursor_col = cursor_col % COLS;
				cursor_row++;
			}
		}
	}
}

// void handle_keyboard_interrupt() {
// 	// Write end of interrupt (EOI)
// 	ioport_out(PIC1_COMMAND_PORT, 0x20);

// 	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
// 	// Lowest bit of status will be set if buffer not empty
// 	// (thanks mkeykernel)
// 	if (status & 0x1) {
// 		char keycode = ioport_in(KEYBOARD_DATA_PORT);
// 		if (keycode < 0 || keycode >= 128) return;
// 		if (keycode == 28) {
// 			// ENTER : Newline
// 			cursor_row++;
// 			newline();
// 			play_sound(500,10);
// 			cursor_col = 0;
// 			// Handle command
// 			if (streq(command_buffer, command_len, "shutdown", 8)) {
// 				shutdown_vm();
//             } else if (streq(command_buffer, command_len, "restart", 7)){
//                 reboot();
//             } else if (streq(command_buffer, command_len, "halt", 4)) {
//                 halt(1);
//             } else if (streq(command_buffer, command_len, "beep", 4)) {
//                 play_sound(500,500);
//             } else if (streq(command_buffer, command_len, "randomnumber", 12)) {
//                 newline();
//                 int x = rand_r(420);
//                 print_int(x);
//                 cursor_row++;
// 				newline();
// 			} else if (streq(command_buffer, command_len, "clear", 5)) {
// 				clear_screen();
// 				cursor_row = 0;
// 			} else if (streq(command_buffer, command_len, "exit", 4)) {
// 				return;		
// 			} else if (streq(command_buffer, command_len, "cli", 3)) {
// 				CLI();
// 				newline();
// 				print("cli");
// 				cursor_row += 1;			
// 			} else if (command_len < 1) {
// 				// do nothing
// 			} else {
// 				play_sound(200,30);
// 				print("Command not found: ");
// 				print(command_buffer);
// 				newline();
// 				cursor_row++;
// 			}
// 			command_len = 0;
//             command_buffer[0];
// 		} else if (keycode == 14) {
// 			// BACKSPACE: Move back one unless on prompt
// 			// if (cursor_col > PROMPT_LENGTH) {
// 				print_char_with_asm(' ', cursor_row, --cursor_col);
// 			// }
// 		} else {
// 			if (command_len >= COMMAND_BUFFER_SIZE) return;
// 			command_buffer[command_len++] = keyboard_map[keycode];
// 			printchar(keyboard_map[keycode], cursor_row, cursor_col++);
// 			play_sound(800,5);
// 			if (cursor_col >= COLS) {
// 				cursor_col = cursor_col % COLS;
// 				cursor_row++;
// 			}
// 		}
// 	}
// }

// void type_handle_keyboard_interrupt() {
// 	// Write end of interrupt (EOI)
// 	ioport_out(PIC1_COMMAND_PORT, 0x20);

// 	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
// 	// Lowest bit of status will be set if buffer not empty
// 	// (thanks mkeykernel)
// 	if (status & 0x1) {
// 		char keycode = ioport_in(KEYBOARD_DATA_PORT);
// 		if (keycode < 0 || keycode >= 128) return;
// 		if (keycode == 28) {
// 			// ENTER : Newline
// 			cursor_row++;
// 			cursor_col = 0;
// 		} else if (keycode == 14) {
// 			// BACKSPACE: Move back one unless on prompt
// 			if (cursor_col > PROMPT_LENGTH) {
// 				print_char_with_asm(' ', cursor_row, --cursor_col);
// 			}
// 		} else {
// 			if (command_len >= COMMAND_BUFFER_SIZE) return;
// 			command_buffer[command_len++] = keyboard_map[keycode];
// 			printchar(keyboard_map[keycode], cursor_row, cursor_col++);
// 			play_sound(800,5);
// 			if (cursor_col >= COLS) {
// 				cursor_col = cursor_col % COLS;
// 				cursor_row++;
// 			}
// 		}
// 	}
// }

// void menu_handle_keyboard_interrupt() {
// 	// Write end of interrupt (EOI)
// 	ioport_out(PIC1_COMMAND_PORT, 0x20);

// 	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
// 	// Lowest bit of status will be set if buffer not empty
// 	// (thanks mkeykernel)
// 	if (status & 0x1) {
// 		char keycode = ioport_in(KEYBOARD_DATA_PORT);
// 		if (keycode < 0 || keycode >= 128) return;
// 		if (keycode == 28) {
// 			// ENTER : Newline
// 			cursor_row++;
// 			play_sound(500,10);
// 			cursor_col = 0;
// 			// Handle command
// 			if (streq(command_buffer, command_len, "1", 1)) {
// 				shutdown_vm();
//             } else if (streq(command_buffer, command_len, "2", 1)){
//                 reboot();
//             } else if (streq(command_buffer, command_len, "3", 1)) {
//                 halt(1);
//             } else if (streq(command_buffer, command_len, "4", 1)) {
//                 play_sound(500,500);
//             } else if (streq(command_buffer, command_len, "5", 1)) {
//                 newline();
//                 int x = rand_r(420);
//                 print_int(x);
//                 cursor_row++;
// 			} else if (command_len < 1) {
// 				// do nothing
// 			} else {
// 				play_sound(200,30);
// 			}
// 			command_len = 0;
//             command_buffer[0];
// 		} else if (keycode == 14) {
// 			// BACKSPACE: Move back one unless on prompt
// 			if (cursor_col > PROMPT_LENGTH) {
// 				print_char_with_asm(' ', cursor_row, --cursor_col);
// 			}
// 		} else {
// 			if (command_len >= COMMAND_BUFFER_SIZE) return;
// 			command_buffer[command_len++] = keyboard_map[keycode];
// 			printchar(keyboard_map[keycode], cursor_row, cursor_col++);
// 			play_sound(800,5);
// 			if (cursor_col >= COLS) {
// 				cursor_col = cursor_col % COLS;
// 				cursor_row++;
// 			}
// 		}
// 	}
// }

static inline void memoryset(void *dst, uint8 value, size_t n) {
    uint8 *d = dst;

    while (n-- > 0) {
        *d++ = value;
    }
}

static inline void *memorycopy(void *dst, const void *src, size_t n) {
    uint8 *d = dst;
    const uint8 *s = src;

    while (n-- > 0) {
        *d++ = *s++;
    }

    return d;
}

static inline void *memorymove(void *dst, const void *src, size_t n) {
    // OK since we know that memcpy copies forwards
    if (dst < src) {
        return memorycopy(dst, src, n);
    }

    uint8 *d = dst;
    const uint8 *s = src;

    for (size_t i = n; i > 0; i--) {
        d[i - 1] = s[i - 1];
    }

    return dst;
}

void enable_cursor(uint8 cursor_start, uint8 cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor() {
	outw(0x3D4, 0x0A);
	outw(0x3D5, 0x20);
}

void SetCursorPosition(uint16 position)
{
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8)(position & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8)((position >> 8) & 0xFF));

	cursor_pos = position;
}

int PositionFromCoords(int x, int y)
{
	return y * 80 + x;
}

#endif


