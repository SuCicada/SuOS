//
// Created by SuCicada on 2/8/2022.
//
#include "typedef.h"
#include "memory.h"
#include "list.c" // todo

/**
1. Best Fit
2. 排序
3.

0x00400000 开始分配

## mft block (map free table block)
    MemoryBlock

## data block:

 one data block in memory:
 [ ][ ][ ][ ][.........]
  ^        ^
  | 4byte  |
 [ data.size][..data...]
    ^         ^
    |         |
 data_flag   *ptr

 */

/** 8 byte
 注意: 不同于 data block
 */
struct MemoryBlock {
    unsigned int start_address; // data address, exclude flag
    unsigned int size; // data size, exclude flag size
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


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#define mem_size_t unsigned int


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
    MemoryBlock full_free_block = {
            memory_map_table.start_address,
            memory_map_table.memory_size
    };
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
    ListNode *pre = NULL;
    while (node != NULL) {
        MemoryBlock *block = list_node_get_value(node);
//        printf("%p\n", block);
        if (block->size >= block_size) break;
//        printf("%d %d\n", block->size, block_size);
        pre = node;
        node = node->next;
    }
//    printf("?????? %p %p\n", node, node->next);

    // 内存表记录
    void *res = NULL;
    if (node != mft->tail) {
        MemoryBlock *free_block = list_node_get_value(node);
        free_block->size -= block_size;

        // 记录 data block 的大小
        *(unsigned int *) free_block->start_address = data_size;

        res = (void *) free_block->start_address + flag_size;
        // 正好空下的大小一样
        if (free_block->size == 0) {
            // 删除 mft 记录
            // remove this node
            list_delete_after_node(mft, pre);

        } else {
            // 空闲块的开头部分被占用了
            free_block->start_address = free_block->start_address + block_size;
        }
    }
    memory_map_table.memory_used += block_size;
    return res;
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"

void mem_free(void *ptr) {
    int flag_size = sizeof(mem_size_t);
    mem_size_t start_address = (mem_size_t) ptr - flag_size;
    mem_size_t data_size = *((mem_size_t *) start_address);
    mem_size_t block_size = data_size + flag_size;

    List *mft = memory_map_table.memory_free_table;
    // 找相邻块
    ListNode *node = mft->head;

    /*
     [xxx] : allocated block
     [...] : free block

    [xxx][xxx][...][xxx][xxx][xxx][...][xxx][xxx]
     2.1             1   2.2    3            2.3
     * */
//    size_t pre_end_address = 0;
    ListNode *pre_node = NULL;
    ListNode *need_add_node = NULL;
    bool is_need_add_node = FALSE;
    while (node != NULL) {
        MemoryBlock *free_block = list_node_get_value(node);
        mem_size_t pre_end_address = free_block->start_address + free_block->size;
        mem_size_t end_address = start_address + block_size;
        // 释放空间
        // 情况 1
        if (pre_end_address == start_address) {
            free_block->size += block_size;
            break;
        }

        // 情况 3
        if (free_block->start_address == end_address) {
            free_block->start_address = start_address;
            free_block->size += block_size;
            break;
        }

        if (free_block->start_address > start_address) {
            if (pre_node != NULL) {
                // 2.2
                // add new node, after pre, before pre->next
                // 注意这里不是 data block, 不管 data flag
                need_add_node = pre_node;

            } else {
                // 情况 2.1
                // 是第一个比它大的块, 说明它前面没有 free_block
                // add new node before list->head
                need_add_node = NULL;
            }
            is_need_add_node = TRUE;
            break;
        }
        pre_node = node;
        node = node->next;
    }

    if (node == NULL) {
        // 2.3
        // 是最后一个块, 说明它后面没有 free_block
        // add new node after list->tail
        need_add_node = mft->tail;
        is_need_add_node = TRUE;
    }

    if (is_need_add_node == TRUE) {
        MemoryBlock new_free_block = {start_address, block_size};
        list_add_after_node(mft, need_add_node, &new_free_block);
    }

    memory_map_table.memory_used -= block_size;
}

#pragma clang diagnostic pop

#pragma clang diagnostic pop
