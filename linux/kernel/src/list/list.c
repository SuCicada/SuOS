//
// Created by SuCicada on 2/23/2022.
//

#include "list.h"
#include "arraymem.h"

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

void *list_node_get_value(ListNode *node) {
    return node->value_ptr;
}

// 注意这里
int list_get_node_type_size(int value_type_size) {
    return (int) sizeof(ListNode *) + value_type_size;
}

void list_init(List *list, ArrayMemory *arraymem, int value_type_size) {
    list->arraymem = arraymem;
    list->type_size = value_type_size;
    list->head = NULL;
    list->tail = list->head;
}

/** copy s2 to s1 */
void memcpy(void *s1, const void *s2, unsigned int n) {
    for (int i = 0; i < n; i++) {
        *((char *) s1++) = *((char *) s2++);
    }
}

unsigned int list_size(List *list) {
    return list->arraymem->size;
}

ListNode *list_new_node(List *list, void *value_ptr) {
    ListNode *new_node = (ListNode *) arraymem_malloc(list->arraymem);
    // 写入 struct 中 next 变量之后的下一段空间
    void *value_data = &new_node->next + 1;
    new_node->value_ptr = value_data;
    new_node->next = NULL;
    //    printf("%x %x %d \n", new_node->value_ptr, value_ptr, list->type_size);
    memcpy(value_data, value_ptr, list->type_size);
//    printf("?????? %p %p\n", new_node, new_node->next);
//    new_node->value_ptr = value_ptr;

    return new_node;
}

void list_add_after_node(List *list, ListNode *pre, void *value_ptr) {
    // need add
    ListNode *node = list_new_node(list, value_ptr);
    if (pre == NULL) {
        list->head = node;
        return;
    }

    node->next = pre->next;
    pre->next = node;
    if (pre == list->tail) {
        list->tail = node;
    }
}

void list_delete_after_node(List *list, ListNode *pre) {
    ListNode *need_delete;
    if (pre == NULL) {
        // remove head
        need_delete = list->head;
        list->head = need_delete->next;
    } else {
        need_delete = pre->next;
        pre->next = need_delete->next;
    }
    arraymem_free(list->arraymem, need_delete);

}
