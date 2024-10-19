#include <stddef.h>
#include <stdbool.h>

#define memory_size 100

bool memalloc(int memory[memory_size][memory_size], int pid);
bool memset(int memory[memory_size][memory_size], int pid, int addr, int val);
int memread(int memory[memory_size][memory_size], int pid, int addr);
bool memfree(int memory[memory_size][memory_size], int pid);

bool memalloc(int memory[memory_size][memory_size], int pid){
    if(memory[pid][0] != 0 || pid >= memory_size){
        return false;
    }else{
        memory[pid][0] = 1;
        int i;
        for (i = 1; i != memory_size; i++){
            memory[pid][i] = 0;
        }
        return true;
    }
}

bool memset(int memory[memory_size][memory_size], int pid, int addr, int val){
    if (memory[pid][0] != 1 || !((addr != 0) && !(addr > memory_size - 1)) || pid >= memory_size){
        return false;
    }else{
            memory[pid][addr] = val;
            return true;
    }
    
}

int memread(int memory[memory_size][memory_size], int pid, int addr){
    if(memory[pid][0] != 1){
        return true;
    }else{
        return memory[pid][addr];
    }
}

bool memfree(int memory[memory_size][memory_size], int pid){
    if (memory[pid][0] != 1 || pid >= memory_size){
        return false;
    }else{
        int i;
        for (i = 0; i != memory_size; i++){
            memory[pid][i] = 0;
        }
        return true;
    }
}