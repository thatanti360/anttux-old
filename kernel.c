#include "kernel.h"
#include "kernel_funcs.h"

//1: extern assembly finally works! :) the syntax is diffrent but that's not a (very big) problem. (at least now lol)

//2: changed from gnu assembler (ew) to nasm! also had to change the linker code. keyboard here i come!
//let's see if extern asm. still works...

//3: yes! it worked! :) but for some reason firefox and vscode freezed after exiting qemu... prob. unrelatable
//now that i know that anttux works it's time to go v6.0k2!

//4: YESSS!!!! THE KEYBOARD WORKS! :D but it's kind of glitchy

//5: made a little game, works like a charm! :D :D :) :)

//6: now v6.0k3

//7: btw it also runs on real hardware so that's cool

//8: i can now ssh into my linux laptop to a windows one then transfer the test.iso and running it (still) with qemu, all on windows

//9: so typing more than 100 characters crashes the computer. BROKEN PLIZ FIX

//10: that was eazy lol

//11: made a linux vm

extern void start();

void kernel_entry()
{
	int index = 0;
  	//first init vga with fore & back colors
  	init_vga(BLUE,WHITE);
  	anttux_init();
	print_bar();
	print("Currently in Useless Text Editor\n\n");
	print_bar();
	cursor_row += 7;
  	init_idt();
  	kb_init();
  	enable_interrupts();
	//HOLY CRAP THE KEYBOARD WORKS!
	play_sound(600,50);
	//player_ready();
	enable_cursor(1,1);
	newline();
	print(check_vm());
	print(" | ");
	print("CPUID: ");
	print_int(get_model());
	newline();
	print_bar();
	for (int i = 0; i < 18; i++)
	{
		newline();	
	}
	for (int i = 0; i < 80; i++)
	{
		print_char('A' + 154);	
	}
	handle_keyboard_interrupt();





	// int *index = 0;
	// for (int i = 0; i < 2000; i++)	
	// {
	// 	print_char_color('A' + 154,index);
	// 	index -= rand_r(rand_r(rand_r(420)));
	// }
	// index -= rand_r(rand_r(rand_r(4260)));
	// clear_screen();
	


  
	while(1);
}
