#include <stdbool.h>

char numb_to_char(int numb);


/*
char scancode_to_ascii(int scnacode){
    unsigned char scancd[] = {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x00 - 0x0F
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',   // 0x10 - 0x1E
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,       // 0x1F - 0x2C
        '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '   // 0x2D - 0x39
    };
    return scancd[scnacode];
}
*/

char numb_to_char(int numb){
    return numb + '0';
}
