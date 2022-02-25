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
(1 + sizeof(unsigned int) + sizeof(MemoryBlock) ) * map_table_size
int main() {
//    mem_init_config(0x00400000, 1024 * 1024 * 10);
    printf("%d\n", sizeof(MEMORY_MAP_TABLE));
}
