#include <stdbool.h>
#include <stdint.h>

void printchar(const char ascii, int wier, int kolu, int col);
void printstring(char* msg, int wier, int kolu, int col);
void example_lines(int del, int startcolor, int size, bool cls, char ascii);
void delay(int s);
void clear_screen(int col);
void clear_line(int wier, int col);
/*
char read_ascii_from_screen(int kolu, int wier);
int read_color_from_screen(int kolu, int wier);
void roll_screen(int i);
*/

typedef struct  
{
    char character;
    uint8_t color;
}scrchar;


void printchar(const char ascii, int wier, int kolu, int col){
    char *vid = (char *)0xb8000;
    int poz = (wier * 80 + kolu) * 2;
    vid[poz ] = ascii;
    vid[poz + 1] = col;
}

void printstring(char* msg, int wier, int kolu, int col){
    while (*msg)
    {
        printchar(*msg++, wier, kolu++, col);
    }
    
}

/*
char read_ascii_from_screen(int kolu, int wier){
    scrchar* vid = (scrchar *)0xb8000;
    int poz = (wier * 80 + kolu) * 2;
    return vid[poz].character;
}

int read_color_from_screen(int kolu, int wier){
    scrchar* vid = (scrchar *)0xb8000;
    int poz = (wier * 80 + kolu) * 2;
    return vid[poz].color;
}

void roll_screen(int i){
    clear_line(0, 0x00);

}
*/
void clear_screen(int col){
   int z;
    for (z = 0; z != 25; z++)
    {
        clear_line(z, col);
    }
}

void clear_line(int wier, int col){
    int i;
    for (i = 0; i != 80; i++){
        printchar(' ', wier, i, col);
    }
}

//example graphics lines(delay, starting color, size max poz, cls = clear when poz is max, char to display)
void example_lines(int del, int startcolor, int size, bool cls, char ascii){
    int kol=0;
    while (true)
    {
        if (kol == size){
            kol=0;
            if (cls){clear_screen(0x00);}
        }
        printchar(ascii, 0, kol++, startcolor);
        startcolor++;
        delay(del);
    }
    
}
