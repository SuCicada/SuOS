//
// Created by SuCicada on 2/23/2022.
//

#include "list.h"
#include "../memory/arraymem.h"

struct ListNode {
    int value;
    struct ListNode *next;
};
#define ListNode struct ListNode
struct List {
    ArrayMemory *arraymem;
    ListNode *head;
    int size;
};

#define List struct List

void list_init(ArrayMemory *arraymem) {

}
