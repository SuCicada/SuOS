//
// Created by SuCicada on 2/8/2022.
//

#include "memory.h"
#include "list.c" // todo

/**
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

=============  struct =========
 MEMORY_MAP_TABLE{

    MemoryBlock
}
 */

/**
 8 byte
*/
struct MemoryBlock {
    unsigned int start_address;
    unsigned int size;
};
#define MemoryBlock struct MemoryBlock

/**
 12 byte
*/
struct MEMORY_MAP_TABLE {
//    int map_table_size;
    unsigned int start_address;
    unsigned int memory_size; // equals to end_address
    List *memory_free_table; // [MemoryBlock] table of free space
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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

void *mem_alloc(unsigned int data_size) {
    // 多个4byte用来放内存块尺寸
    int flag_size = sizeof(unsigned int);
    unsigned int block_size = data_size + flag_size;
    List *mft = memory_map_table.memory_free_table;

    ListNode *node = mft->head;
    ListNode **pre = &(mft->head);
    while (node != mft->tail) {
        MemoryBlock *block = node->value_ptr;
        if (block->size >= block_size) break;
        pre = &node;
        node = node->next;
    }
    void *res = NULL;
    if (node != mft->tail) {
        MemoryBlock *free_block = node->value_ptr;
        free_block->size -= block_size;

        // 记录 free_block 的大小
        *(unsigned int *) free_block->start_address = data_size;

        res = (void *) free_block->start_address + flag_size;
        if (free_block->size == 0) {
            // remove this node
            (*pre)->next = node->next;
            arraymem_free(mft->arraymem, node);

        } else {
            // 空闲块的开头部分被占用了
            free_block->start_address = free_block->start_address + block_size;
        }
    }
    return res;
}

#pragma clang diagnostic pop

/**
one block in memory:
 [ ][ ][ ][ ][.........]
  ^        ^
  | 4byte  |
 [ data.size][..data...]
              ^
              |
              *ptr

 */
void mem_free(void *ptr) {
    unsigned int data_size = *(((unsigned int *) ptr) - 4);

}
