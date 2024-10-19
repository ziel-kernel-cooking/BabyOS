#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define memory_size 100
#define line_length 80
#define max_row 25
#define commands_number 80

void delay(int s);
unsigned char odklaw();
void panic(char *msg);

void printchar(const char ascii, int wier, int kolu, int col);
void printstring(const char* msg, int wier, int kolu, int col);
void clear_screen(int col);
void clear_line(int wier, int col);
void roll_screen();

void delay(int s){
    s *= 1000;
    for (s; s != 0; s--){
    }
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ __volatile__ ("outb %0, %1" : : "a"(value), "Nd"(port));
}

unsigned char odklaw(){
    unsigned char ret;
    outb(0x20, 0x64);
    if ((inb(0x64) & 1)){
        ret = inb(0x60);
    }
    return ret;
}

void panic(char *msg){
    clear_screen(0x00);
    printstring("Kernel panic because:", 0, 0, 0x0f);
    printstring(msg, 1, 0, 0x0f);
    while (1);
}
