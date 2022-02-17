//
// Created by SuCicada on 2/14/2022.
//

#include <stdio.h>
#include "../kernel/src/rbtree/rbtree.c"

void node_show(RB_Node *node) {
//    if (node->color == 1)
    printf("%5d %5d %5d \n", node->index, node->value, node->color);
}

#define nodes_num 10

void show(RB_Tree *tree) {
//    for (int i = 0; i < 10; i++)
//        printf("%2d |", i);
//    printf("\n");
    printf("index value color \n");
    for (int i = 0; i < tree->capacity; i++) {
        RB_Node *n = tree_get_node(tree, i);
        node_show(n);
    }
    printf("\n");
}

int main() {
    int need_add[] = {
            2,
            1,
            3,
            4
    };
    RB_Tree tree;
    RB_Tree *tree_ptr = &tree;
    RB_Node nodes[nodes_num];
    tree_init(tree_ptr, nodes, sizeof(nodes) / sizeof(RB_Node));
    for (int i = 0; i < sizeof(need_add) / sizeof(int); i++) {
//        tree_add(tree_ptr, need_add[i]);
    }
    show(tree_ptr);
//    int res = find(2);
//    printf("res %d\n", res);
}
