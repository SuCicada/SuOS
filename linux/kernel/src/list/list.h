//
// Created by SuCicada on 2/23/2022.
//
#include "arraymem.h"

#ifndef SUOS_LIST_H
#define SUOS_LIST_H

struct ListNode {
    void *value_ptr; // 虽然是指针，但因为我们要适配泛型，所以这里最后指向的是一段真实空间
    struct ListNode *next;
    // ... value data ... (真实空间中, 这后面就存着值数据了)
};
#define ListNode struct ListNode

struct List {
    ArrayMemory *arraymem;
    int type_size;
    ListNode *head;
    ListNode *tail;
};
#define List struct List


void list_init(List *list, ArrayMemory *arraymem, int value_type_size);

int list_get_node_type_size(int value_type_size);

void *list_node_get_value(ListNode *node);

unsigned int list_size(List *list);

ListNode *list_new_node(List *list, void *value_ptr);

void list_add_after_node(List *list, ListNode *pre, void *value_ptr);

void list_delete_after_node(List *list, ListNode *pre);


#endif //SUOS_LIST_H
