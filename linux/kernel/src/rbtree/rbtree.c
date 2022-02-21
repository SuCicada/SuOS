//
// Created by SuCicada on 2/9/2022.
//

#include "rbtree.h"
#include "arraylist.c"
// todo 之后可以做成泛型

#define RB_Node_Red 1
#define RB_Node_Black 2

struct RB_Node {
//    int index;
    char color;
    int value;
    struct RB_Node *left;
    struct RB_Node *right;
};

#define RB_Node struct RB_Node
#define RB_Node_Array RB_Node*
//#define Array(t) t*

struct RB_Tree {
//    RB_Node arr[50];
    ArrayList *nodes_mem; // RB_Node* arr[]
    RB_Node *root;
    //    int capacity;
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
#define RB_Node_Left 1
#define RB_Node_Right 2

#define bool int
#define TRUE 1
#define FALSE 0

#ifdef NULL
#define TEMP_NULL NULL
#undef NULL
#endif
#define NULL ((void*)0)

//void tree_init(RB_Tree *tree, RB_Node nodes[], int capacity) {
void tree_init(RB_Tree *tree, ArrayList *nodes_mem, int capacity) {
    tree->nodes_mem = nodes_mem;
    tree->root = NULL;
//    tree->capacity = capacity;
//    for (int i = 0; i < capacity; i++) {
//        RB_Node *node = tree->nodes[i];
//        node->index = i;
//        node->value = NULL;
//        node->color = NULL;
//    }
}


RB_Node *tree_get_node(RB_Tree *tree, int i) {
    if (i < tree->capacity)
        return tree->nodes[i];
    else
        return NULL;
}

RB_Node *tree_get_root(RB_Tree *tree) {
    return tree_get_node(tree, 0);
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
    int father_index = node_father(node->index);
    int uncle_index = father_index + (father_index % 2) * 1;
    return tree_get_node(tree, uncle_index);
}

RB_Node *tree_node_get_grandfather(RB_Tree *tree, RB_Node *node) {
    return tree_get_node(tree, node_father(node_father(node->index)));
}

//bool tree_node_empty(RB_Tree *tree, RB_Node *node) {
//    return tree_get_node(tree, node->index)->color == NULL;
}

bool node_empty(RB_Node *node) {
    return node->color == NULL;
}

void tree_node_left_rotate(RB_Tree *tree, RB_Node *node) {

}

void tree_node_right_rotate(RB_Tree *tree, RB_Node *node) {

}

RB_Node *find0(RB_Tree *tree, RB_Node *current,
               int n, bool is_update);


bool node_is_root(RB_Node *node) {
    return node->index == 0;
}

int node_get_branch_direction(RB_Node *node) {
    return node->index % 2 == 1 ? RB_Node_Left : RB_Node_Right;
}

void node_set_color(RB_Node *node, char color) {
    node->color = color;
}

RB_Node *find(RB_Tree *tree, int n) {
    RB_Node *root = tree_get_root(tree);
    return find0(tree, root, n, FALSE);
}

/**
 current_node: where site of node which will put
 */
bool tree_auto_balance(RB_Tree *tree, RB_Node *current_node) {
//    current_node->value = value;
    if (node_is_root(current_node)) {
        // 1. empty tree
        current_node->color = RB_Node_Black;
        return TRUE;
    }

    RB_Node *father_node = tree_node_get_father(tree, current_node);
    char father_node_color = father_node->color;
    if (father_node_color == RB_Node_Black) {
        // 2. current_node 's father is black
        current_node->color = RB_Node_Red;
        return TRUE;

    } else if (father_node_color == RB_Node_Red) {
        // 3. father is red
        RB_Node *uncle_node = tree_node_get_uncle(tree, current_node);
        bool uncle_node_is_empty = node_empty(uncle_node);
        RB_Node *grandfather_node = tree_node_get_grandfather(tree, current_node);

        if (!uncle_node_is_empty &&
            uncle_node->color == RB_Node_Red) {
            // 3.1 father is red, and uncle node is red
            node_set_color(father_node, RB_Node_Black);
            node_set_color(uncle_node, RB_Node_Black);
            node_set_color(grandfather_node, RB_Node_Red);
            tree_auto_balance(tree, grandfather_node);
            return TRUE;

        } else if (uncle_node_is_empty ||
                   uncle_node->color == RB_Node_Black) {
            // 3.2 uncle is black or empty
            int branch_direction = node_get_branch_direction(current_node);
            if (branch_direction == RB_Node_Right) {
                // 3.2.1 father is red, uncle is black. current is right children
                tree_node_left_rotate(tree, father_node);
                return TRUE;

            } else if (branch_direction == RB_Node_Left) {
                // 3.2.2 father is red, uncle is black. current is left children
                node_set_color(father_node, RB_Node_Black);
                node_set_color(grandfather_node, RB_Node_Red);
                tree_node_right_rotate(tree, father_node);
                return TRUE;

            }

        }
    }
    return TRUE;
}

int node_value_compare(int a, int b) {
    // todo
    return a - b;
}

RB_Node *find0(RB_Tree *tree, RB_Node *current,
               int value, bool is_update) {
    if (node_empty(current)) {
//        printf("empty \n");
        if (is_update) {
//            node_data_set(current, n);
            current->value = value;
            tree_auto_balance(tree, current);
            return current;
        }
        return NULL;
    }
//    printf("%d %d ?????\n", value, current->index);
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
