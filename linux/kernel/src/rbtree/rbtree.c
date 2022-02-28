//
// Created by SuCicada on 2/9/2022.
//
#include "typedef.h"
#include "rbtree.h"
#include "memory/arraymem.c"
// todo 之后可以做成泛型

#define RB_Node_Red 1
#define RB_Node_Black 2

struct RB_Node {
//    int index;
    char color;
    int value;
    struct RB_Node *left;
    struct RB_Node *right;
    struct RB_Node *parent;
};

#define RB_Node struct RB_Node
#define RB_Node_Array RB_Node*
//#define Array(t) t*

struct RB_Tree {
//    RB_Node arr[50];
    ArrayMemory *nodes_mem; // RB_Node* arr[]
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
 node.parent= int(i / 2) = int(node.index-1 / 2)
 */
#define node_left(i) ((i) * 2 + 1)
#define node_right(i) ((i) * 2 + 2)
#define node_father(i) ((int)(((i)-1)/2))
#define node_data_get(i) (arr[i])
#define node_data_set(i, d) (arr[i]=(d))
//#define tree_node_is_root(i) ((i)==0)
#define RB_Node_Root 0
#define RB_Node_Left 1
#define RB_Node_Right 2

#define NULL ((void *)0)

//void tree_init(RB_Tree *tree, RB_Node nodes[], int capacity) {
void tree_init(RB_Tree *tree, ArrayMemory *nodes_mem, int capacity) {
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


//RB_Node *tree_get_node(RB_Tree *tree, int i) {
//    if (i < tree->capacity)
//        return tree->nodes[i];
//    else
//        return NULL;
//}

//RB_Node *tree_get_root(RB_Tree *tree) {
//    return tree_get_node(tree, 0);
//}

//RB_Node *tree_node_get_left(RB_Tree *tree, RB_Node *node) {
//    return tree_get_node(tree, node_left(node->index));
//}
//
//RB_Node *tree_node_get_right(RB_Tree *tree, RB_Node *node) {
//    return tree_get_node(tree, node_right(node->index));
//}
//
//RB_Node *tree_node_get_father(RB_Tree *tree, RB_Node *node) {
//    return tree_get_node(tree, node_father(node->index));
//}
void tree_set_root(RB_Tree *tree, RB_Node *node) {
    node->parent = NULL;
    tree->root = node;
}

RB_Node *node_get_grandfather(RB_Node *node) {
//    return tree_get_node(tree, node_father(node_father(node->index)));
    return node->parent->parent;
}

RB_Node *node_get_uncle(RB_Node *node) {
//    int father_index = node_father(node->index);
//    int uncle_index = father_index + (father_index % 2) * 1;
//    return tree_get_node(tree, uncle_index);
    RB_Node *parent = node->parent;
    RB_Node *grandfather = parent->parent;
    return grandfather->left == parent ? grandfather->right : grandfather->left;
}


//bool tree_node_empty(RB_Tree *tree, RB_Node *node) {
//    return tree_get_node(tree, node->index)->color == NULL;
//}

//bool node_empty(RB_Node *node) {
//    return node->color == NULL;
//}

/** 狸猫换太子
 *  before: p is node->parent
 *  after:  p is new_node->parent
 * */
void tree_node_reset_parent(RB_Tree *tree, RB_Node *node, RB_Node *new_node) {
    RB_Node *parent = node->parent;
    if (parent == NULL) {
        tree_set_root(tree, new_node);

    } else {
        if (parent->left == node)
            parent->left = new_node;
        else if (parent->right == node)
            parent->right = new_node;

        new_node->parent = parent;
    }
}

/**
 X is current

  [X]                Y
  / \               / \
 a   Y     ==>     [X] d
    / \           /  \
   c   d         a    c

 */
void node_left_rotate(RB_Tree *tree, RB_Node *node) {
    RB_Node *right = node->right;
    // 换老爹
    tree_node_reset_parent(tree, node, right);

    // 换犬子
    node->right = right->left;

    // 身份颠倒
    node->parent = right;
    right->left = node;
}

/**
 Y is current

    [Y]            X
    / \           /  \
   X   d  ==>    a   [Y]
  / \                / \
 a   c              c   d

 */
void tree_node_right_rotate(RB_Tree *tree, RB_Node *node) {
    RB_Node *left = node->left;
    // 换老爹
    tree_node_reset_parent(tree, node, left);

    // 换犬子
    node->left = left->right;

    // 身份颠倒
    node->parent = left;
    left->right = node;
}


bool tree_node_is_root(RB_Tree *tree, RB_Node *node) {
//    return node->index == 0;
    return tree->root == node;
}

int node_get_branch_direction(RB_Node *node) {
//    return node->index % 2 == 1 ? RB_Node_Left : RB_Node_Right;
    return node->parent->left == node ?
           RB_Node_Left : RB_Node_Right;
}

void node_set_color(RB_Node *node, char color) {
    node->color = color;
}

bool tree_auto_balance(RB_Tree *tree, RB_Node *current_node);

/**
 */
RB_Node *tree_add_node(RB_Tree *tree,
                       int value) {
    RB_Node *node = (RB_Node *) arraymem_malloc(tree->nodes_mem);
    node->left = node->right = NULL;
    node->value = value;
    return node;
}

void tree_node_rotate(RB_Tree *tree, RB_Node *node, int direction_flag) {
    switch (direction_flag) {
        case RB_Node_Left:
            node_left_rotate(tree, node);
            break;
        case RB_Node_Right:
            tree_node_right_rotate(tree, node);
            break;
        default:
            break;
    }
}

bool tree_auto_balance(RB_Tree *tree, RB_Node *current_node) {
    if (tree_node_is_root(tree, current_node)) {
        // 1. empty tree
        current_node->color = RB_Node_Black;
        return TRUE;
    }
//    current_node->color = RB_Node_Red;

    RB_Node *parent_node = current_node->parent;
//    char father_node_color = parent_node->color;
    if (parent_node->color == RB_Node_Black) {
        // 2. current_node 's parent is black
        return TRUE;

    } else if (parent_node->color == RB_Node_Red) {
        // 3. parent is red
        RB_Node *uncle_node = node_get_uncle(current_node);
//        bool uncle_node_is_empty = uncle_node == NULL;
        RB_Node *grandfather_node = node_get_grandfather(current_node);

        if (uncle_node != NULL &&
            uncle_node->color == RB_Node_Red) {
            // 3.1 parent is red, and uncle node is red
            node_set_color(parent_node, RB_Node_Black);
            node_set_color(uncle_node, RB_Node_Black);
            node_set_color(grandfather_node, RB_Node_Red);
            tree_auto_balance(tree, grandfather_node);
            return TRUE;

        } else if (uncle_node == NULL ||
                   uncle_node->color == RB_Node_Black) {
            // 3.2 parent is red, uncle is black or empty
            int current_branch_direction = node_get_branch_direction(current_node);
            int parent_branch_direction = node_get_branch_direction(parent_node);

            if (parent_branch_direction != current_branch_direction) {
                // 3.2.1 parent is red, uncle is black or empty.
                // parent is right, current is left. ( right rotate )
                // parent is left, current is right. ( left rotate )
                tree_node_rotate(tree, parent_node, parent_branch_direction);

                parent_node = current_node;
            }

            // parent_branch_direction == current_branch_direction
            // 3.2.2 parent is red, uncle is black or empty.
            // parent is right, current is right ( left rotate ) or
            // parent is left, current is left  ( right rotate )
            node_set_color(parent_node, RB_Node_Black);
            node_set_color(grandfather_node, RB_Node_Red);
            tree_node_rotate(tree, grandfather_node,
                             parent_branch_direction == RB_Node_Black ? RB_Node_Red : RB_Node_Black);
            return TRUE;
        }
    }
    return TRUE;
}

int node_value_compare(int a, int b) {
    // todo
    return a - b;
}

/**
todo
 parent:      current's parent
 current_ptr: current's parent's children's ptr
 */
RB_Node *find0(RB_Tree *tree,
               RB_Node *current,
               int value,
               RB_Node **_return_parent_ptr,
               RB_Node ***_return_parent_children_ptr_ptr
) {

//    RB_Node *current = *current_ptr;
    if (current == NULL) {
//        if (is_add) {
//            RB_Node *new_node = tree_add_node(tree, parent, current_ptr, value);
////            *current_ptr = new_node;
////            tree_auto_balance(tree, new_node);
//
//            return new_node;
//        }
        return NULL;
    }
//    printf("%d %d ?????\n", value, current->index);
    int current_value = current->value;
    int compare_res = node_value_compare(value, current_value);
    if (compare_res == 0) {
        return current;
    }

    RB_Node **next_node_ptr;
    if (compare_res < 0) { // in left
        next_node_ptr = &current->left;
    } else { // in right
        next_node_ptr = &current->right;
    }

    if (_return_parent_ptr != NULL)
        *_return_parent_ptr = current;
    if (_return_parent_children_ptr_ptr != NULL)
        *_return_parent_children_ptr_ptr = next_node_ptr;

    RB_Node *next_node = *next_node_ptr;
    return find0(tree, next_node, value, _return_parent_ptr, _return_parent_children_ptr_ptr);
}

RB_Node *tree_find(RB_Tree *tree, int value) {
    RB_Node *root = tree->root;
    return find0(tree, root, value, NULL, NULL);
}

RB_Node *tree_add(RB_Tree *tree, int value) {
    RB_Node *root = tree->root;
    RB_Node *res_parent;
    RB_Node **res_parent_children_ptr;
    RB_Node *new_node = tree_add_node(tree, value);

    if (root != NULL) {
        RB_Node *res = find0(tree, root, value, &res_parent, &res_parent_children_ptr);
        if (res) {
            // 如果已经存在怎么办
            return NULL;
        }
        new_node->parent = res_parent;

        // parent->children = new_node
        *res_parent_children_ptr = new_node;
    } else {
        tree_set_root(tree, new_node);
    }
    new_node->color = RB_Node_Red;

    tree_auto_balance(tree, new_node);
    return new_node;
}

