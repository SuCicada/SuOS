//
// Created by SuCicada on 2/21/2022.
//

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
struct ArrayList {
    void *array; // real_capacity = (type_size + 1) * capacity
    int type_size;
    int capacity;
    int real_capacity;
    int end;
    int size; // current how many allocated
};
#define ArrayList struct ArrayList

#define ArrayList_Node_Allocated_Flag ((char)0xfc)
#define NULL ((void *)0)

/** real space == (type_size + 1) * capacity
*/
void arraylist_init(ArrayList *arraylist, void *array, int type_size, int capacity) {
    arraylist->array = array;
    arraylist->type_size = type_size;
    arraylist->capacity = capacity;
    arraylist->end = 0;
    arraylist->size = 0;
    int real_full_space = (type_size + 1) * capacity;
    arraylist->real_capacity = real_full_space;
}

void *arraylist_malloc(ArrayList *arraylist) {
    if (arraylist->size == arraylist->capacity) {
        return NULL;
    }

    void *node = arraylist->array + arraylist->end;
    int next_index = arraylist->end;

    // 一直找, 找到空的空间
    while (*(char *) node == ArrayList_Node_Allocated_Flag) {

        next_index = next_index + 1 + arraylist->type_size;
        if (next_index >= arraylist->real_capacity) {
            next_index -= arraylist->real_capacity;
        }

        node = arraylist->array + next_index;
    }
    arraylist->end = next_index;
    arraylist->size++;
    *(char *) (node) = ArrayList_Node_Allocated_Flag;
    void *data_ptr = node + 1;
    return data_ptr;
}

void arraylist_free(ArrayList *arraylist, void *data_ptr) {
    // remove the allocated-flag
    *(char *) (data_ptr - 1) = 0;
    arraylist->size--;
}
