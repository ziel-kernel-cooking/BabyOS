#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define memory_size 100
#define line_length 80
#define max_row 25
#define commands_number 80


void printchar(const char ascii, int wier, int kolu, int col);
void printstring(const char* msg, int wier, int kolu, int col);
void clear_screen(int col);
void clear_line(int wier, int col);
void delay(int s);
void panic(char *msg);
unsigned char odklaw();
bool comp_2_strings(char *str1, char *str2, int size);
void strcpy(char *msg, char *list, int count);
int strlen(char *string);
int string_to_int(const char *str);


char read_ascii_from_screen(int kolu, int wier);
int read_color_from_screen(int kolu, int wier);
void roll_screen();
char scan_to_ascii(int scan);

bool memalloc(int memory[memory_size][memory_size], int pid);
bool memset(int memory[memory_size][memory_size], int pid, int addr, int val);
int memread(int memory[memory_size][memory_size], int pid, int addr);
bool memfree(int memory[memory_size][memory_size], int pid);

void intToString(int num, char str[]);
void exec(int addr);
void write_to_ram(int addr, int data);
int read_from_ram(int addr);

void init_commands(char commands[commands_number][10]){
    strcpy("listcmd", commands[0], 7); // list all commands
    strcpy("clear", commands[1], 5); //clears the screen
    strcpy("set", commands[2], 3); // set value to memory on adress
    strcpy("get", commands[3], 3); //gets and prints value of the memory on adrress
    strcpy("exec", commands[4], 4); //executes program at adress in ram
    strcpy("wram", commands[5], 4); // writes data to ram
    strcpy("rram", commands[6], 4); // reads from ram
}

void splitcommand(char line[line_length], char splitedcomm[5][10]){
    int i = 0;
    int cc = 0;

    if (line[i] == 0){return;}
    while (line[i] != ';')
    {
        splitedcomm[0][cc] = line[i];
        cc++;
        i++;
    }
    cc = 0;
    i++;
    if (line[i] == 0){return;}

    while (line[i] != ';')
    {
        splitedcomm[1][cc] = line[i];
        cc++;
        i++;
    }

    cc = 0;
    i++;
    if (line[i] == 0){return;}

    while (line[i] != ';')
    {
        splitedcomm[2][cc] = line[i];
        cc++;
        i++;
    }

    cc = 0;
    i++;
    if (line[i] == 0){return;}

    while (line[i] != ';')
    {
        splitedcomm[3][cc] = line[i];
        cc++;
        i++;
    }
    
}

void handle_commands(char commands[commands_number][10], char line[line_length], int memory[memory_size][memory_size]){
    int i;
    char splitedcomm[5][10] = {0};
    int com = -1;
    bool synterr = true;
    char tempchar[10];
    int tempint;

    int cx = memory[0][3];
    int cy = memory[0][4];
    int col = memory[0][5];
    
    for (i = 0; i != line_length - 1; i++){
        if (line[i] != 0){
            synterr = true;
        }
        if (line[i] == ';'){
            synterr = false;
        }
        if (line[i] == ' '){
            break;
        }
    }

    if (synterr){
        if(cy < max_row - 1){
            printstring("Syntax error!", cy, 0, col);
            memory[0][4]++;
        }else{
            roll_screen();
            printstring("Syntax error!", max_row - 1, 0, col);
        }
        return;
    }

    splitcommand(line, splitedcomm);

    for (i = 0; i != commands_number - 1; i++){
        if (comp_2_strings(commands[i], splitedcomm[0], 10)){
            com = i;
        }
    }

    int arg1int = string_to_int(splitedcomm[1]);
    int arg2int = string_to_int(splitedcomm[2]);
    int arg3int = string_to_int(splitedcomm[3]);  

    switch (com)
    {
    case 0:
        if(cy != max_row){
            printchar('/', cy, 0, col);
            cy++;
        }else{
            roll_screen();
            printchar('/', max_row - 1, 0, col);
        }

        for (i = arg1int; i != arg2int; i++){
            if (cy >= max_row -1){
                roll_screen();
                printstring(commands[i], max_row - 1, 0, col);
            }else{
                printstring(commands[i], cy, 0, col);
                cy++;
            }
        }
        memory[0][4] = cy;
        return;

    case 1:
        clear_screen(col);
        memory[0][4] = 0;
        memory[0][3] = 0;
        return;

    case 2:
        memory[arg1int][arg2int] = arg3int;

        if(cy != max_row){
            printstring("/done", memory[0][4], 0, col);
            memory[0][4]++;
        }else{
            roll_screen();
            printstring("/done", max_row - 1, 0, col);
        }

        return;

    case 3:
        intToString(memory[arg1int][arg2int], tempchar);
        if(cy != max_row){
            printstring("/", cy, 0, col);
            cy++;
        }else{
            roll_screen();
            printstring("/", max_row - 1, 0, col);
            roll_screen;
        }

        if(cy != max_row){
            printstring(tempchar, cy, 0, col);
            cy++;
        }else{
            roll_screen();
            printstring(tempchar, max_row - 1, 0, col);
        }
        memory[0][4] = cy;
        return;

    case 4:
        clear_screen(col);
        exec(arg1int);
        if(cy != max_row){
            printstring("/done", cy, 0, col);
            cy++;
        }else{
            roll_screen();
            printstring("/done", max_row - 1, 0, col);
        }
        memory[0][4] = cy;
        return;

    case 5:
        write_to_ram(arg1int, arg2int);
        if(cy != max_row){
            printstring("/done", cy, 0, col);
            cy++;
        }else{
            roll_screen();
            printstring("/done", max_row - 1, 0, col);
        }
        memory[0][4] = cy;
        return;

    case 6:
        tempint = read_from_ram(arg1int);
        intToString(tempint, tempchar);
        if(cy != max_row){
            printstring("/", cy, 0, col);
            cy++;
        }else{
            roll_screen();
            printstring("/", max_row - 1, 0, col);
            roll_screen;
        }

        if(cy != max_row){
            printstring(tempchar, cy, 0, col);
            cy++;
        }else{
            roll_screen();
            printstring(tempchar, max_row - 1, 0, col);
        }
        memory[0][4] = cy;
        return; 

    default:
        if(cy != max_row){
            printstring("Command not found!", cy, 0, col);
            cy++;
        }else{
            roll_screen();
            printstring("Command not found!", max_row - 1, 0, col);
        }
        memory[0][4] = cy;
        return;
    }
}