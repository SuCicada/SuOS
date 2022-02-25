//
// Created by SuCicada on 2/23/2022.
//

#include "list.h"
#include "arraymem.h"

struct ListNode {
    void *value_ptr;
    struct ListNode *next;
};
#define ListNode struct ListNode
struct List {
    ArrayMemory *arraymem;
    ListNode *head;
    ListNode *tail;
};

#define List struct List

int list_size(List *list) {
    return list->arraymem->size;
}

void list_init(List *list, ArrayMemory *arraymem) {
    list->arraymem = arraymem;
}

void list_add(List *list, void *value_ptr) {
    ListNode *node = (ListNode *) arraymem_malloc(list->arraymem);
    node->value_ptr = value_ptr;
}

void list_remove(List *list) {

}
