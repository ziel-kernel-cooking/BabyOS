#include <stdbool.h>


char numb_to_char(int numb);
char scan_to_ascii(int scan);

char numb_to_char(int numb){
    return numb + '0';
}

char* int_to_string(){
    
}

char scan_to_ascii(int scan){
    unsigned char ascii_table[] = {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',    // 0x00 - 0x0F
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',      // 0x10 - 0x1F
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',             // 0x20 - 0x2C
        0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,               // 0x2D - 0x39
        '*', 0, ' ', 0                                                              // 0x3A - 0x3F
    };
    if (scan < sizeof(ascii_table) / sizeof(ascii_table[0])) {
        return ascii_table[scan];
    }
    return 0;
}

bool comp_2_strings(char *str1, char *str2, int size){
    int i;
    for (i = 0; i != size - 1; i++){
        if(str1[i] == str2[i]){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

void strcpy(char *msg, char *list, int count){
    int i;
    for (i = 0; i != count; i++){
        list[i] = msg[i];
    }
}

int strlen(char *string){
    int i;
    while (*string)
    {
        *string++;
        i++;
    }
    return i;
}

int string_to_int(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            return 0;
        }
        i++;
    }

    return result * sign;
}

void reverseString(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void intToString(int num, char str[]) {
    int i = 0;
    int isNegative = 0;

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num != 0);

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverseString(str, i);
}