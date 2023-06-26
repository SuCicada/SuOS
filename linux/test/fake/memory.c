//
// Created by SuCicada on 2023/06/22.
//

#include <stdlib.h>

unsigned int memtest(unsigned int start, unsigned int end) {}
unsigned int memtest_sub(unsigned int start, unsigned int end) {}
void mem_init_config(unsigned int start_address, unsigned int memory_size) {}
unsigned int mem_get_used_size() {}
void *mem_alloc(unsigned int data_size) {
    return malloc(data_size);
}

void mem_free(void *ptr) {
    free(ptr);
}
