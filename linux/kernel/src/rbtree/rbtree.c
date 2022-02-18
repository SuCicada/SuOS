//
// Created by SuCicada on 2/9/2022.
//

#include "rbtree.h"

// todo 之后可以做成泛型

#define RB_Node_Red 1
#define RB_Node_Black 2

struct RB_Node {
    int index;
    char color;
    int value;
};

#define RB_Node struct RB_Node
#define RB_Node_Array RB_Node*
//#define Array(t) t*

struct RB_Tree {
//    RB_Node arr[50];
    RB_Node_Array nodes; // RB_Node arr[]
    int capacity;
};

#define RB_Tree struct RB_Tree


/**
 tree.sum    = 2 ** tree.depth - 1
 tree.bottom = 2 ** (tree.depth - 1)

    2**1-1  1       2
 1  2  3   4   5   6   7
 0 00 01 000 001 010 011

 0  1  2   3   4   5    6
// (level begin from 1, index begin from 0, i begin form 1)
 node.left  = (index+1)*2-1   = node.index * 2 + 1
 node.right = (index+1)*2-1+1 = node.index * 2 + 2
 node.father= int(i / 2) = int(node.index-1 / 2)
 */
#define node_left(i) ((i) * 2 + 1)
#define node_right(i) ((i) * 2 + 2)
#define node_father(i) ((int)(((i)-1)/2))
#define node_data_get(i) (arr[i])
#define node_data_set(i, d) (arr[i]=(d))
//#define node_is_root(i) ((i)==0)

#define bool int
#define TRUE 1
#define FALSE 0

#ifdef NULL
#define TEMP_NULL NULL
#undef NULL
#endif
#define NULL 0

void tree_init(RB_Tree *tree, RB_Node nodes[], int capacity) {
    tree->nodes = nodes;
    tree->capacity = capacity;
    for (int i = 0; i < capacity; i++) {
        RB_Node *node = &tree->nodes[i];
        node->index = i;
        node->value = NULL;
        node->color = NULL;
    }
}

RB_Node *tree_get_root(RB_Tree *tree) {
    return &tree->nodes[0];
}

RB_Node *tree_get_node(RB_Tree *tree, int i) {
    if (i < tree->capacity)
        return &tree->nodes[i];
    else
        return NULL;
}

RB_Node *tree_node_get_left(RB_Tree *tree, RB_Node *node) {
    return tree_get_node(tree, node_left(node->index));
}

RB_Node *tree_node_get_right(RB_Tree *tree, RB_Node *node) {
    return tree_get_node(tree, node_right(node->index));
}

RB_Node *tree_node_get_father(RB_Tree *tree, RB_Node *node) {
    return tree_get_node(tree, node_father(node->index));
}

RB_Node *tree_node_get_uncle(RB_Tree *tree, RB_Node *node) {

}

RB_Node *tree_node_get_grandfather(RB_Tree *tree, RB_Node *node) {
    return tree_get_node(tree, node_father(node_father(node->index)));
}

bool tree_node_empty(RB_Tree *tree, RB_Node *node) {
    return tree_get_node(tree, node->index)->color == NULL;
}

RB_Node *find0(RB_Tree *tree, RB_Node *current,
               int n, bool is_update);


bool node_is_root(RB_Node *node) {
    return node->index == 0;
}

RB_Node *find(RB_Tree *tree, int n) {
    RB_Node *root = tree_get_root(tree);
    return find0(tree, root, n, FALSE);
}

/**
 node_site: where site of node which will put
 */
bool add0(RB_Tree *tree, RB_Node *node_site, int value) {

    node_site->value = value;
    if (node_is_root(node_site)) {
        // 1. empty tree
        node_site->color = RB_Node_Black;
        return TRUE;
    }

    char father_color = tree_node_get_father(tree, node_site)->color;
    if (father_color == RB_Node_Black) {
        // 2. node_site 's father is black
        node_site->color = RB_Node_Red;

    } else if (father_color == RB_Node_Red) {
        if ()

    }
    return TRUE;
}

int node_value_compare(int a, int b) {
    // todo
    return a - b;
}

RB_Node *find0(RB_Tree *tree, RB_Node *current,
               int value, bool is_update) {
    if (tree_node_empty(tree, current)) {
        printf("empty \n");
        if (is_update) {
//            node_data_set(current, n);
            add0(tree, current, value);
            return current;
        }
        return NULL;
    }
    printf("%d %d ?????\n", value, current->index);
    int current_value = current->value;
    int compare_res = node_value_compare(value, current_value);
    if (compare_res == 0) {
        return current;
    } else if (compare_res < 0) {
        // in left
        RB_Node *left_node = tree_node_get_left(tree, current);
        return find0(tree, left_node, value, is_update);
    } else {
        // in right
        RB_Node *right_node = tree_node_get_right(tree, current);
        return find0(tree, right_node, value, is_update);
    }
}

bool tree_add(RB_Tree *tree, int value) {
    RB_Node *root = tree_get_root(tree);
    return find0(tree, root, value, TRUE) != NULL;
}


#ifdef TEMP_NULL
#undef NULL
#define NULL TEMP_NULL
#undef TEMP_NULL
#endif
