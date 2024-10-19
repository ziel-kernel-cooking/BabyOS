#include <stdbool.h>
#include <stdint.h>

void printchar(const char ascii, int wier, int kolu, int col);
void printstring(const char* msg, int wier, int kolu, int col);
void delay(int s);
void clear_screen(int col);
void clear_line(int wier, int col);

char read_ascii_from_screen(int kolu, int wier);
int read_color_from_screen(int kolu, int wier);
void roll_screen();

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

void printstring(const char* msg, int wier, int kolu, int col){
    while (*msg)
    {
        printchar(*msg++, wier, kolu++, col);
    }
    
}


char read_ascii_from_screen(int kolu, int wier){
    scrchar* vid = (scrchar *)0xb8000;
    int poz = (wier * 80 + kolu);
    return vid[poz].character;
}

int read_color_from_screen(int kolu, int wier){
    scrchar* vid = (scrchar *)0xb8000;
    int poz = (wier * 80 + kolu);
    return vid[poz].color;
}


void roll_screen(){
    clear_line(0, 0x00);
    int cx = 0;
    int cy = 0;
    int maxw = 24;
    int maxk = 79;

    int i;
    int k;
    char tempch;
    int tempcol;
    for (i = 0; i != maxw; i++){
        for (k = 0; k != maxk; k++){
            printchar('@', i, k, 0x0f);
            tempch = read_ascii_from_screen(k, i+1);
            tempcol = read_color_from_screen(k, i+1);
            printchar(tempch, i, k, tempcol);
        }
    }
    clear_line(24, 0x00);
}


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


