#include "kernel.h"
#include "kernel_funcs.h"

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
