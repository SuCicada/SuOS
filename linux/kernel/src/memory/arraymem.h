//
// Created by SuCicada on 2/23/2022.
//
#ifndef SUOS_ARRAYMEM_H
#define SUOS_ARRAYMEM_H


/**

数组实现的微型内存分配 (只支持固定大小的 block)

 - 支持泛型

node space schema:

index:  0   1   2  ....
data:  [__][__][__]....

if node is allocated:
index:   0     1   2  ....
data:  [0xfc][xx][xx]....
    the data of index from 1 to .... are user's data

 */
struct ArrayMemory {
    void *array; // real_capacity = (type_size + 1) * capacity
    int type_size;
    int capacity;
    int real_capacity;
    int end;
    int size; // current how many allocated
};
#define ArrayMemory struct ArrayMemory

#define ArrayMemory_Node_Allocated_Flag ((char)0xfc)
#define NULL ((void *)0)

void arraymem_init(ArrayMemory *arraymem, void *array, int type_size, int capacity);

void *arraymem_malloc(ArrayMemory *arraymem);

void arraymem_free(ArrayMemory *arraymem, void *data_ptr);

#endif //SUOS_ARRAYMEM_H
