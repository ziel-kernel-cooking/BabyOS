#include <stdbool.h>
#include <stddef.h>

#define memory_size 100
#define line_length 80
#define max_row 25


void printchar(const char ascii, int wier, int kolu, int col);
void printstring(const char* msg, int wier, int kolu, int col);
void clear_screen(int col);
void clear_line(int wier, int col);
void delay(int s);
void panic(char *msg);
char numb_to_char(int numb);
unsigned char odklaw();


char read_ascii_from_screen(int kolu, int wier);
int read_color_from_screen(int kolu, int wier);
void roll_screen();
char scan_to_ascii(int scan);

bool memalloc(int memory[memory_size][memory_size], int pid);
bool memset(int memory[memory_size][memory_size], int pid, int addr, int val);
int memread(int memory[memory_size][memory_size], int pid, int addr);
bool memfree(int memory[memory_size][memory_size], int pid);

void terminal(int memory[memory_size][memory_size], char line[line_length]);

extern void _start(){
    clear_screen(0x00);
    
    printstring("Welcome to the BabyOS kernel!", 0, 0, 0x0f);
    printstring("This OS is dedicated to Terrence Andrew Davis, one of the smartests programmers in the world", 1, 0, 0x0f);
    printstring("Type listcmd;(all commands must end with ;) to list all the commands!", 3, 0, 0x0f);

    char line[line_length] = {0};
    int memory[memory_size][memory_size] = {0};
    terminal(memory, line);
    
    while (1);
}