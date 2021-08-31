#include <cpuid.h>
#include "kernel.h"

//kernel_funcs is preeeeettttttyyyy funky 

//index for video buffer array
uint32 vga_index;
//counter to store new lines
static uint32 next_line_index = 1;
//fore & back color values
uint8 g_fore_color = WHITE, g_back_color = BLUE;
//digit ascii code for printing integers
int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

//Stop the PC Speaker.
void nosound() {
 	uint8 tmp = inb(0x61) & 0xFC;
 
 	outb(0x61, tmp);
}


void play_sound(uint32 nFrequence, int time) {
 	uint32 Div;
 	uint8 tmp;
 
  //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8) (Div) );
 	outb(0x42, (uint8) (Div >> 8));
 
  //And play the sound using the PC speaker
 	tmp = inb(0x61);
  if (tmp != (tmp | 3)) {
 	outb(0x61, tmp | 3);
 	}
  sleep(time);
  nosound();
  
 }

/*
16 bit video buffer elements(register ax)
8 bits(ah) higher : 
  lower 4 bits - forec olor
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/
uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color)
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

void clear_screen() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printchar(' ', i, j);
		}
	}
}

//clear video buffer array
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
  uint32 i;
  for (i = 0; i < BUFSIZE; i++)
  {
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }
  next_line_index = 1;
  vga_index = 0;
}

//initialize vga buffer
void init_vga(uint8 fore_color, uint8 back_color)
{
  vga_buffer = (uint16 *)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
  g_fore_color = fore_color;
  g_back_color = back_color;
}

/*
increase vga_index by width of row(80)
*/
void newline()
{
  if (next_line_index >= 55)
  {
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80 * next_line_index;
  next_line_index++;
}

//assign ascii character to video buffer
void print_char(char ch)
{
  if(ch == '\n')
  {
    newline();
  }
  else
  {
    vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
    vga_index++;
  }
}

void print_bool(bool bo)
{
  if (bo == true)
  {
    print("True");
  }
  else
  {
    print("False");
  }
  
  
}

uint32 strlen(const char *str)
{
  uint32 length = 1;
  while (str[length])
    length++;
  return length + 1;
}

uint32 digit_count(int num)
{
  uint32 count = 0;
  if (num == 0)
    return 1;
  while (num > 0)
  {
    count++;
    num = num / 10;
  }
  return count;
}

void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if (num == 0 && dgcount == 1)
  {
    number[0] = '0';
    number[1] = '\0';
  }
  else
  {
    while (num != 0)
    {
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

void print_ra(char *str)
{
  //print_ra("");
  uint32 index = 0;
  while (str[index])
  {
    print_char(str[index]);
    index++;
  }
  vga_index = 0;
  clear_vga_buffer(str[strlen(str)],g_fore_color,g_back_color);
}

//print string by calling print_char
void print(char *str)
{
  uint32 index = 0;
  while (str[index])
  {
    print_char(str[index]);
    index++;
  }
}

void sleep(int delay)
{
  int num = delay * 1000000;
  for (int i = 0; i < num; i++)
  {
    asm volatile("nop");
  }
}

void print_withdelay(char *str, int delay)
{
  uint32 index = 0;
  while (str[index])
  {
    print_char(str[index]);
    index++;
    sleep(delay);
  }
}

//print int by converting it into string
//& then printing string
void print_int(int num)
{
  char str_num[digit_count(num) + 1];
  itoa(num, str_num);
  print(str_num);
}


void halt(int cause)
{
  newline();
  newline();
  print("System halted.");
  newline();
  switch (cause)
  {
  case 0:
    print("Cause: Code execution done.");
    newline();
    break;
  case 1:
    print("Cause: User halted system.");

  default:
    break;
  }
  while(1)
  {
    asm volatile("hlt");
  }
}

void print_bar()
{
  for (int i = 0; i < 80; i++)
  {
    print_char('-');
  }
  
}

static void play_sound_always(uint32 nFrequence) {
 	uint32 Div;
 	uint8 tmp;
 
  //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8) (Div) );
 	outb(0x42, (uint8) (Div >> 8));
 
  //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
  }
}

int rand_r (unsigned int *seed)
{
  unsigned int next = *seed;
  int result;

  next *= 1103515245;
  next += 12345;
  result = (unsigned int) (next / 65536) % 2048;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  *seed = next;

  return result;
}



void shutdown_vm()
{
  newline();
  newline();
  print("Shutting down the VM in a few moments...");
  sleep(5000);
  //qemu 2.0, bochs
  outw(0xB004, 0x2000);
  //qemu
  outw(0x604, 0x2000);
  //virtualbox
  outw(0x4004, 0x3400);
  sleep(250);
  panic("Could not shutdown, are you running Anttux on a real machine?");
  halt(0);
}
 
void reboot()
{
    uint8 temp;
 
    asm volatile ("cli"); /* disable all interrupts */
 
    /* Clear all keyboard buffers (output and command buffers) */
    do
    {
        temp = inb(KBRD_INTRFC); /* empty user data */
        if (check_flag(temp, KBRD_BIT_KDATA) != 0)
            inb(KBRD_IO); /* empty keyboard data */
    } while (check_flag(temp, KBRD_BIT_UDATA) != 0);
 
    outb(KBRD_INTRFC, KBRD_RESET); /* pulse CPU reset line */
loop:
    asm volatile ("hlt"); /* if that didn't work, halt the CPU */
    goto loop; /* if a NMI is received, halt again */
}

//assign ascii character to video buffer
void print_char_color(char ch, uint8 color)
{
  if(ch == '\n')
  {
    newline();
  }
  else
  {
    vga_buffer[vga_index] = vga_entry(ch, color, g_back_color);
    vga_index++;
  }
}

void print_char_color_all(char ch, uint8 fore, uint8 back)
{
	if (ch == '\n')
	{
		newline();
	}
	else
	{
		vga_buffer[vga_index] = vga_entry(ch, fore, back);
		vga_index++;
	}
}

//print string by calling print_char
void print_color(char *str, uint8 color)
{
  uint32 index = 0;
  while (str[index])
  {
    print_char_color(str[index], color);
    index++;
  }
}

void print_color_all(char *str, uint8 fore, uint8 back)
{
	uint32 index = 0;
	while (str[index])
	{
		print_char_color_all(str[index], fore, back);
		index++;
	}
}

void anttux_init()
{
  for (int i = 0; i < 31; i++)
  {
    print_char('A' + 154);
  }
  print_color_all(ANTTUX_VERSION,WHITE,BLUE);
  for (int i = 0; i < 33; i++)
  {
    print_char('A' + 154);
  }
  newline();
  print("Welcome to ");
  print(ANTTUX_VERSION);
  print("!");
  newline();
}

/* Example: Get CPU's model number */
static int get_model(void)
{
    int ebx, unused;
    __cpuid(0, unused, ebx, unused, unused);
    return ebx;
}
 
/* Example: Check for builtin local APIC. */
static int check_apic(void)
{
    unsigned int eax, unused, edx;
    __get_cpuid(1, &eax, &unused, &unused, edx);
    return edx & CPUID_FEAT_EDX_APIC;
}

char *check_vm()
{
  int cpuid = get_model();
  if(cpuid == 1752462657)
  {
    return "Qemu";
  } else if(cpuid == 1970169159) {
    return "VirtualBox";
  } else {
    return "i don't know";
  }
}

void aybabtu()
{
  panic("All your base are belong to us.");
}

void panic(char *error_string)
{
  CLI();
  nosound();
  disable_cursor();
  clear_screen();
  init_vga(GREY,RED);
  for (int i = 0; i < 32; i++)
  {
    print_char('A' + 154);
  }
  print("!!!PANIC!!!");
  for (int i = 0; i < 37; i++)
  {
    print_char('A' + 154);
  }
  newline();
  newline();
  print("Anttux ran into a problem :(\n\n");
  print("\nMessage: ");
  print(error_string);
  print("\n\n\n");
  for (int i = 0; i < 31; i++)
  {
    print_char('A' + 154);
  }
  print("???DETAILS???");
  for (int i = 0; i < 36; i++)
  {
    print_char('A' + 154);
  }
  newline();
  newline();

  print("Virtual 8086 Enabled: ");
  print_bool(detect_v86());
  newline();

  print("CPU Model Number: ");
  print_int(get_model());
  newline();

  print("APIC Check: ");
  print_bool(check_apic());
  newline();

  print("\n\n");
  print("Anttux will reboot the computer in a few moments...");

  print("\n\n\n\n\n\n\n\n\n");

  for (int i = 0; i < 80; i++)
  {
    print_char('A' + 154);
  }

  sleep(15000);



  reboot();


  while(1) { asm volatile("hlt"); }
}

int player_x = 0;
int player_y = 0;
char player_char = 'A' + 193; //154 or 193
int player_size = 1;

void player_update_pos()
{
  switch (player_size)
  {
  case 2:
    print_char_with_asm(player_char,player_y,player_x);
    print_char_with_asm(player_char,player_y,player_x+1);
    print_char_with_asm(player_char,player_y+1,player_x);
    print_char_with_asm(player_char,player_y+1,player_x+1);
    print_char_with_asm(player_char,player_y,player_x+2);
    print_char_with_asm(player_char,player_y+1,player_x);
    print_char_with_asm(player_char,player_y+1,player_x+2);
    break;
  
  case 1:
    print_char_with_asm(player_char,player_y,player_x); 
    break;

  default:
    break;
  }
  
}

void player_ready()
{
  player_update_pos();
  bool player_ready = true;
  int player_char = 0;
}

void player_move_right(int r_move)
{
  if(player_ready)
  {
    clear_screen();
    clear_vga_buffer(' ',g_fore_color,g_back_color);
    player_x += r_move; 
    player_update_pos();
  }
}

void player_move_left(int l_move)
{
  if(player_ready)
  {
    clear_screen();
    clear_vga_buffer(' ',g_fore_color,g_back_color);
    player_x -= l_move; 
    player_update_pos();
  }
}

void player_move_up(int u_move)
{
  if(player_ready)
  {
    clear_screen();
    clear_vga_buffer(' ',g_fore_color,g_back_color);
    player_y -= u_move; 
    player_update_pos();
  }
}

void player_move_down(int d_move)
{
  if(player_ready)
  {
    clear_screen();
    clear_vga_buffer(' ',g_fore_color,g_back_color);
    player_y += d_move; 
    player_update_pos();
  }
}

void player_change_size(int charac)
{
  if(player_ready)
  {
    switch (charac)
    {
    case 1:
      player_size = 1;
      break;
    case 2:
      player_size = 2;
      break;
    default:
      player_size = 2;
      break;
    }
  }
}

void player_change_char(char pc)
{
  char player_char = pc;
}

void player_collision(int x_pos, int y_pos)
{

}
