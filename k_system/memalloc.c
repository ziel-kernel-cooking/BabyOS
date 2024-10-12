#include <stddef.h>
#define BLOCK_SIZE 4096
/*
void init_memalocc(void* memstart, size_t memsize);
void* memalloc();
void freemem(void* block);

typedef struct memblock
{
    struct memblock* next;
    
} memblock;

memblock* free_list = NULL;

void init_memalocc(void* memstart, size_t memsize){
    size_t block_count = memsize / BLOCK_SIZE;
    free_list = (memblock*)memstart;

    memblock* current = free_list;

    for (size_t i = 0; i < block_count - 1; i++){
        current->next = (memblock*)((char*)current + BLOCK_SIZE);
        current = current->next;
    }
    current->next = NULL;
}

void* memalloc(){
    if (free_list == NULL){
        return NULL;
    }

    memblock* block = free_list;
    free_list = free_list->next;

    return (void*)block;
}

void freemem(void* block){
    ((memblock*)block)->next = free_list;
    free_list = (memblock*)block;
}
*/