#include <stdbool.h>
#include <stddef.h>

void printchar(const char ascii, int wier, int kolu, int col);
void printstring(char* msg, int wier, int kolu, int col);
void clear_screen(int col);
void clear_line(int wier, int col);
void example_lines(int del, int startcolor, int size, bool cls, char ascii);
char numb_to_char(int numb);
void delay(int s);
unsigned char inb(unsigned short port);
void panic(char *msg);
/*
char read_ascii_from_screen(int kolu, int wier);
int read_color_from_screen(int kolu, int wier);
void roll_screen(int i);


void init_memalocc(void* memstart, size_t memsize);
void* memalloc();
void freemem(void* block);
*/

extern void _start(){
    clear_screen(0x00);
    example_lines(1000, 0x00, 2000, true, ' ');
    while (1);
}