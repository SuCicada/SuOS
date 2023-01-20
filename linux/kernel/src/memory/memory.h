//
// Created by ZQ091606 on 2/8/2022.
//

#ifndef SUOS_MEMORY_H
#define SUOS_MEMORY_H

#include "list.h"
#include "typedef.h"
#include "arraymem.h"

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
#define MEMORY_START_ADDRESS 0x00400000

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

extern MEMORY_MAP_TABLE memory_map_table;
extern List memory_free_table_list;
extern ArrayMemory arraymem;

// ==================== memory check =======================
#define EFLAGS_AC_BIT        0x00040000
#define CR0_CACHE_DISABLE    0x60000000

unsigned int memtest(unsigned int start, unsigned int end);

unsigned int memtest_sub(unsigned int start, unsigned int end);

// ==================== memory manage =================

void mem_init_config(unsigned int start_address, unsigned int memory_size);

unsigned int mem_get_used_size();

void *mem_alloc(unsigned int data_size);

void mem_free(void *ptr);

#define mem_size_t unsigned int

//unsigned int memtest_sub(unsigned int start, unsigned int end);
//
//unsigned int memtest(unsigned int start, unsigned int end);

#endif //SUOS_MEMORY_H
