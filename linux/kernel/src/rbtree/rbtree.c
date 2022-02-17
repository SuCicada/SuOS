//
// Created by SuCicada on 2/9/2022.
//

#include "rbtree.h"


struct RB_Node {
    int index;
    int value;
    char color;
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
#define node_father(i) (int(((i)-1)/2))
#define node_data_get(i) (arr[i])
#define node_data_set(i, d) (arr[i]=(d))
#define node_is_root(i) ((i)==0)

#define bool int
#define TRUE 1
#define FALSE 0
#define NULL 0

void tree_init(RB_Tree *tree, RB_Node nodes[], int capacity) {
    tree->nodes = nodes;
    tree->capacity = capacity;
    for (int i = 0; i < capacity; i++) {
        RB_Node* node = &tree->nodes[i];
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

//int find(RB_Tree *tree, int n);

RB_Node *find0(RB_Tree *tree, RB_Node *current,
               int n, bool is_update);

bool tree_node_empty(RB_Tree *tree, RB_Node *node) {
    return tree_get_node(tree, node->index) == NULL;
}

RB_Node *find(RB_Tree *tree, int n) {
    RB_Node *root = tree_get_root(tree);
    return find0(tree, root, n, FALSE);
}

bool add0(RB_Node *node, int n) {
//    if (node_is_root(i) || node_father(i)){
//    }
    node->value = n;
    node->color = 1;
    return TRUE;
}

RB_Node *find0(RB_Tree *tree, RB_Node *current,
               int n, bool is_update) {
    if (tree_node_empty(tree, current)) {
        if (is_update) {
//            node_data_set(current, n);
            add0(current, n);
            return current;
        }
        return NULL;
    }

    int current_value = current->value;
    if (current_value == n) {
        return current;
    } else if (n < current_value) {
        // in left
        RB_Node *left_node = tree_node_get_left(tree, current);
        return find0(tree, left_node, n, is_update);
    } else {
        // in right
        RB_Node *right_node = tree_node_get_right(tree, current);
        return find0(tree, right_node, n, is_update);
    }
}

bool tree_add(RB_Tree *tree, int n) {
    RB_Node *root = tree_get_root(tree);
    return find0(tree, root, n, TRUE) != NULL;
}
