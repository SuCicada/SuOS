//
// Created by SuCicada on 2/24/2022.
//


/*
debug command;
./run_test.sh test_memory.c -I../kernel/src -I../kernel/src/list -I../kernel/src/memory

 * */
#include "../kernel/src/memory/memory.c"
#include "../kernel/src/memory/arraymem.c"
#include "utils_test.c"

/*

MEMORY_MAP_TABLE: (1 + sizeof(MemoryBlock) ) * map_table_size

 * */

void mem_show() {
    printf("0x%x: %5d/%d (B)\n",
           memory_map_table.start_address, memory_map_table.memory_used, memory_map_table.memory_size);
}

void *test_mem_alloc(int m) {
    void *p;
    printf(GRN"[+] mem_alloc %d\n"RESET, m);
    printf("%4s", "");
    p = mem_alloc(m);
    mem_show();
    printf("%4sres: %p\n", "", p);
    return p;
}

void *test_mem_free(void *p) {
    printf(RED"[-] free %p\n"RESET, p);
    printf("%4s", "");
    mem_free(p);
    mem_show();
}

int main() {
//    mem_init_config(0x00400000, 1024 * 1024 * 10);
    int memory_size = 1024 * 1024 * 10;
    void *start_address = malloc(memory_size);
    mem_init_config((unsigned int) start_address, memory_size);
    printf("%d\n", sizeof(MemoryBlock));

    void *p;
    // test mem_alloc
    p = test_mem_alloc(100);

    // test free
    test_mem_free(p);

    // test malloc and free
    test_mem_alloc(10);
    p = test_mem_alloc(123);
    test_mem_free(p);
}
