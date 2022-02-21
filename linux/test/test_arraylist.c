//
// Created by SuCicada on 2/21/2022.
//

#include <stdio.h>
//#include "../kernel/src/rbtree/rbtree.c"
#include "../kernel/src/rbtree/arraylist.c"

struct RB_Node {
    int index;
    char color;
    int value;
};
#define RB_Node struct RB_Node

//#define size
void arraylist_show(ArrayList *arraylist) {
    printf("===================\n");
    printf("size %d\n", arraylist->size);
    for (int i = 0; i < arraylist->real_capacity; i += 1 + arraylist->type_size) {
        RB_Node *node = (RB_Node *) (arraylist->array + i + 1);
        printf("%2x: ", *(char *) (arraylist->array + i) & 0xfF);
        printf("%d %d %d", node->index, node->color, node->value);
        printf("\n");
    }
}

int main() {
    int type_size = sizeof(RB_Node);
    int capacity = 5;
    int size = (type_size + 1) * capacity;
    char array[size];
    printf("%d\n", size);
    ArrayList arraylist;
    ArrayList *arraylist_ptr = &arraylist;
    arraylist_init(arraylist_ptr, array, type_size, capacity);
    RB_Node *node = (RB_Node *) arraylist_malloc(arraylist_ptr);
    node->index = 1;
    node->color = 11;
    node->value = 111;
    arraylist_show(arraylist_ptr);
    arraylist_free(arraylist_ptr, node);
    arraylist_show(arraylist_ptr);

    node = (RB_Node *) arraylist_malloc(arraylist_ptr);
    node->value = 9883;
    RB_Node *node2 = (RB_Node *) arraylist_malloc(arraylist_ptr);
    node2->value = 23;
    arraylist_show(arraylist_ptr);
    arraylist_free(arraylist_ptr, node);
    for (int i = 0; i < 8; i++) {
        node = (RB_Node *) arraylist_malloc(arraylist_ptr);
        if (node != NULL)
            node->value = i + 100;
        arraylist_show(arraylist_ptr);
    }
}
