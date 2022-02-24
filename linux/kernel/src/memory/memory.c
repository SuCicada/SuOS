//
// Created by SuCicada on 2/8/2022.
//

#include "memory.h"
#include "list.c" // todo

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

struct MemoryBlock {
    int start, size;
};
#define MemoryBlock struct MemoryBlock

struct MEMORY_MAP_TABLE {
    int map_table_size;
    int start_address;
    int memory_size; // equals to end_address
    List *memory_free_table; // table of free space
};
#define MEMORY_MAP_TABLE struct MEMORY_MAP_TABLE
MEMORY_MAP_TABLE memory_map_table;

void *find_free(int size) {

}

void mem_init_config(int start_address, int memory_size) {
    memory_map_table.start_address = start_address;
    memory_map_table.memory_size = memory_size;
//    memory_map_table.memory_map_table
//    memory_map_table.
}

void *mem_register(void *address, int size) {

    List *mft = memory_map_table.memory_free_table;
    ListNode *node = mft->head;
    ListNode **pre = &(mft->head);
    while (node != mft->tail) {
        MemoryBlock *block = node->value_ptr;
        if (block->size >= size) break;
        pre = &node;
        node = node->next;
    }
    if (node != mft->tail) {
        MemoryBlock *block = node->value_ptr;
        block->size -= size;
        if (block->size == 0) {
            // remove this node
            (*pre)->next = node->next;
        }
    }

}

void *mem_alloc(int size) {
    void *new_address = find_free(size);
//    memoryMapTable
}

void mem_free(void *ptr) {

}
