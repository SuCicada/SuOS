//
// Created by SuCicada on 2/21/2022.
//
#include "arraymem.h"
/** real space == (type_size + 1) * capacity
*/
void arraymem_init(ArrayMemory *arraymem, void *array, int type_size, int capacity) {
    arraymem->array = array;
    arraymem->type_size = type_size;
    arraymem->capacity = capacity;
    arraymem->end = 0;
    arraymem->size = 0;
    int real_full_space = (type_size + 1) * capacity;
    arraymem->real_capacity = real_full_space;
}

void *arraymem_malloc(ArrayMemory *arraymem) {
    if (arraymem->size == arraymem->capacity) {
        return NULL;
    }

    void *node = arraymem->array + arraymem->end;
    int next_index = arraymem->end;

    // 一直找, 找到空的空间
    while (*(char *) node == ArrayMemory_Node_Allocated_Flag) {

        next_index = next_index + 1 + arraymem->type_size;
        if (next_index >= arraymem->real_capacity) {
            next_index -= arraymem->real_capacity;
        }

        node = arraymem->array + next_index;
    }
    arraymem->end = next_index;
    arraymem->size++;
    *(char *) (node) = ArrayMemory_Node_Allocated_Flag;
    void *data_ptr = node + 1;
    return data_ptr;
}

void arraymem_free(ArrayMemory *arraymem, void *data_ptr) {
    // remove the allocated-flag
    *(char *) (data_ptr - 1) = 0;
    arraymem->size--;
}
