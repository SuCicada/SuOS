//
// Created by SuCicada on 2/24/2022.
//


/*
debug command;
./run_test.sh test_memory.c -I../kernel/src/list -I../kernel/src/memory

 * */
#include "../kernel/src/memory/memory.c"
#include "../kernel/src/memory/arraymem.c"
#include "stdio.h"
#include "stdlib.h"

/*

MEMORY_MAP_TABLE: (1 + sizeof(MemoryBlock) ) * map_table_size

 * */
void *malloc(size_t __size);

void mem_show() {
    printf("0x%x: %d/%d (B)\n",
           memory_map_table.start_address, memory_map_table.memory_used, memory_map_table.memory_size);
}

int main() {
//    mem_init_config(0x00400000, 1024 * 1024 * 10);
    printf("%d\n", sizeof(MemoryBlock));
    int memory_size = 1024 * 1024 * 10;
    void *start_address = malloc(memory_size);
    mem_init_config((unsigned int)start_address, memory_size);
    mem_show();
    void *p;
    p= mem_alloc(10);
    printf("res: %p\n", p);
    p= mem_alloc(10);
    printf("res: %p\n", p);
}
