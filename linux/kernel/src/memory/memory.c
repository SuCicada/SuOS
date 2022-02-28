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

/** 8 byte */
struct MemoryBlock {
    unsigned int start_address;
    unsigned int size;
};
#define MemoryBlock struct MemoryBlock
// 内存管理表能管理到的内存空闲块的数量
#define map_table_frees 4096

/** 12 byte  */
struct MEMORY_MAP_TABLE {
//    int map_table_size;
    unsigned int start_address;
    unsigned int memory_size; // equals to end_address
    unsigned int memory_used;
    List *memory_free_table; // [MemoryBlock] table of free space
};
#define MEMORY_MAP_TABLE struct MEMORY_MAP_TABLE

MEMORY_MAP_TABLE memory_map_table;
List memory_free_table_list;
ArrayMemory arraymem;

void *find_free(int size) {

}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

void mem_init_config(unsigned int start_address, unsigned int memory_size) {

    // 分配 memory_map_table 的空间
    void *arr = (void *) start_address;
    int list_node_size = list_get_node_type_size(sizeof(MemoryBlock));
    arraymem_init(&arraymem, arr, list_node_size, map_table_frees);
    list_init(&memory_free_table_list, &arraymem, sizeof(MemoryBlock));
    // 分配完 memory_map_table 之后用作用户内存空间
    unsigned int map_table_size = arraymem_get_real_capacity(&arraymem);

    memory_map_table.start_address = start_address + map_table_size;
    memory_map_table.memory_size = memory_size - map_table_size;
    memory_map_table.memory_used = 0;
    memory_map_table.memory_free_table = &memory_free_table_list;

    // 初始化记录全部的空闲空间
    MemoryBlock full_free_block;
    full_free_block.start_address = memory_map_table.start_address;
    full_free_block.size = memory_map_table.memory_size;
    list_add_after_node(&memory_free_table_list, NULL, &full_free_block);
//    printf("init over %x\n", full_free_block);
}


void *mem_alloc(unsigned int data_size) {
    // 多个4byte用来放内存块尺寸
    int flag_size = sizeof(unsigned int);
    // 要申请的块
    unsigned int block_size = data_size + flag_size;

    List *mft = memory_map_table.memory_free_table;

//    printf("?????? \n");
    // 找空闲块
    ListNode *node = mft->head;
    ListNode **pre = &(mft->head);
    while (node != NULL) {
        MemoryBlock *block = list_node_get_value(node);
//        printf("%p\n", block);
        if (block->size >= block_size) break;
//        printf("%d %d\n", block->size, block_size);
        pre = &node;
        node = node->next;
    }
//    printf("?????? %p %p\n", node, node->next);

    // 内存表记录
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
            // 删除 mft 记录
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
