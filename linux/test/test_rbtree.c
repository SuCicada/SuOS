//
// Created by SuCicada on 2/14/2022.
//

#include <stdio.h>
#include "../kernel/src/rbtree/rbtree.c"

void node_show(RB_Node *node) {
//    if (node->color == 1)
    printf("%5d %5d \n", node->value, node->color);
}


void tree_show0(RB_Node *node) {
    if (node) {
        node_show(node);
        if (node->left)
            tree_show0(node->left);
        if (node->right)
            tree_show0(node->right);
    }
}

void tree_show(RB_Tree *tree) {
    tree_show0(tree->root);
    printf("========================\n");
//    for (int i = 0; i < 10; i++)
//        printf("%2d |", i);
//    printf("\n");
//    printf("index value color \n");
//    for (int i = 0; i < tree->capacity; i++) {
//        RB_Node *n = tree_get_node(tree, i);
//        node_show(n);
//    }
//    printf("\n");

}

#define nodes_num 10

int main() {
    // 1 2 3
    // 1 3 5 4
    // 1 3 2
    int need_add[] = {
            1,
            3,
            2,
    };
    RB_Node nodes[nodes_num];
    ArrayList arraylist_data;
    ArrayList *arraylist = &arraylist_data;
    arraylist_init(arraylist, nodes, sizeof(RB_Node), nodes_num);
    RB_Tree tree;
    RB_Tree *tree_ptr = &tree;
    tree_init(tree_ptr, arraylist, sizeof(nodes) / sizeof(RB_Node));

    for (int i = 0; i < sizeof(need_add) / sizeof(int); i++) {
        tree_add(tree_ptr, need_add[i]);
    tree_show(tree_ptr);
    }
//    int res = find(2);
//    printf("res %d\n", res);
}


/*
 关于 RB_Tree* 的变量名的讲究:
 node_site: 代表 node 的位置. 并不指具体的 node. 即指向的空间中不一定有具体数据
 node: 代表确实存在的 node 的位置.


 * */
