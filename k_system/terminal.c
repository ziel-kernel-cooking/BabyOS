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


char read_ascii_from_screen(int kolu, int wier);
int read_color_from_screen(int kolu, int wier);
void roll_screen();
char scan_to_ascii(int scan);

bool memalloc(int memory[memory_size][memory_size], int pid);
bool memset(int memory[memory_size][memory_size], int pid, int addr, int val);
int memread(int memory[memory_size][memory_size], int pid, int addr);
bool memfree(int memory[memory_size][memory_size], int pid);

void init_commands(char commands[commands_number][10]);

void handle_commands(char commands[commands_number][10], char line[line_length], int memory[memory_size][memory_size]);

void cursor(char ascii, int memory[memory_size][memory_size], int pid, int cx, int cy, int col){

    if (memory[pid][1] != 10000){
        memory[pid][1]++;
    }else{
        if(memory[pid][2] == 0){
            printchar(ascii, cy, cx, col);
            memory[pid][2] = 1;
            memory[pid][1] = 0;
        }else{
            printchar(' ', cy, cx, col);
            memory[pid][2] = 0;
            memory[pid][1] = 0;
        }
    }
    if (memory[pid][2] == 0){
        printchar(ascii, cy, cx, col);
    }else{
        printchar(' ', cy, cx, col);
    }
}

void liner(char line[line_length], int cx, int cy, int col){
    int i;
    for (i = 0; i != line_length; i++){
        if (i != cx){
            printchar(line[i], cy, i, col);
        }
    }
    
}

int type(char line[line_length], int scancode, int cx, int cy){
    char temp = scan_to_ascii(scancode);

    if (temp != 0){
        if(cx < line_length){
            line[cx] = temp;
            return cx + 1;
        }else{
            line[line_length] = temp;
            return cx;
        }
    }
    return cx;
}

void handle_key(int memory[memory_size][memory_size], char line[line_length], int scancode, char commands[commands_number][10]){

    switch (scancode)
    {
    case 0x1C:
        printchar(' ', memory[0][4], memory[0][3], memory[0][5]);
        memory[0][4]++;
        memory[0][3] = 0;
        handle_commands(commands, line, memory);
        int i;
        for (i = 0; i != line_length; i++){
            line[i] = 0;
        }
        return;

    case 0x0E:
        if (memory[0][3] > 0){
            line[memory[0][3] - 1] = 0;
            memory[0][3]--;
        }
        return;
    
    default:
        memory[0][3] = type(line, scancode, memory[0][3], memory[0][4]);
        return;
    }
}




void terminal(int memory[memory_size][memory_size], char line[line_length]){
    bool textmode;
    int scancode;
    int i;

    memalloc(memory, 0); // Alllocation for cursor pid = 0

    memory[0][3] = 0; // x axis of cursor
    memory[0][4] = 4; // y axis of cursor
    memory[0][5] = 0x0f; // color for the cursor 
    memory[0][6] = 1; // enable cursor
    memory[0][7] = 1; //enable textmode
    memory[0][8] = '@'; //ascii for cursor

    int cx; //temp for cursor
    int cy; //temp for cursor
    int col; //temp color for the cursor
    bool curs; //temp for enabling cursor
    char ascc; //temp char for cursor

    char commands[80][10] = {0};
    init_commands(commands);

    while (true)
    {
        textmode = (1 == memory[0][7]);
        if (textmode){
            scancode = odklaw();
            
            handle_key(memory, line, scancode, commands);

            cx = memory[0][3];
            cy = memory[0][4];
            col = memory[0][5];
            curs = (1 == memory[0][6]);
            ascc = memory[0][8];


            if (memory[0][3] >= line_length - 1){
                memory[0][3] = line_length - 1;
            }
            if(memory[0][3] <= 0){
                memory[0][3] = 0;
            }
            
            if (cy >= max_row){
                printchar(line[cx], cy, cx, 0x0f);
                for (i = 0; i != line_length; i++){
                    line[i] = ' ';
                }
                roll_screen();
                memory[0][4] = max_row - 1;
            }
            
            if(curs){cursor(ascc, memory, 0, cx, cy, col);}
            liner(line, cx, cy, col);
        }

    }
    
}