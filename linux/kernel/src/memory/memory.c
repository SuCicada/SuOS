//
// Created by SuCicada on 2/8/2022.
//

#include "memory.h"

/*
1. Best Fit
2. 排序
3.

0x00400000 开始分配

mem_map:


memory_init():

malloc => pointer:
    - find match size
    - flag space
    - return pointer

free(pointer):
    - unflag space


 */

struct Memory_Block {
    int start, end;
};
#define Memory_Block struct Memory_Block



void *mem_alloc(int size) {

}

void mem_free(void *ptr) {

}
