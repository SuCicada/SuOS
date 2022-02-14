//
// Created by SuCicada on 2/9/2022.
//

#include "rbtree.h"

void init(int size);
void add(int n);
int find(int n);

const int size = 2<<5-1;
int arr[size];


/*
 tree.sum    = 2 ** tree.depth - 1
 tree.bottom = 2 ** (tree.depth - 1)

    2**1-1  1       2
 1  2  3   4   5   6   7
 0 00 01 000 001 010 011

 0  1  2   3   4   5    6
// (level begin from 1, index begin from 0)
// node.level = node.index
 node.left  = node.index * 2
 node.right = node.index * 2 + 1

 */
#define node_left(i) (i * 2)
#define node_right(i) (i * 2+1)
#define node_data_get(i) (arr[i])
#define node_data_set(i,d) (arr[i]=d)

#define bool int
#define TRUE 1
#define FALSE 0

int node_empty(int n){
    return node_data(current) == NULL;
}
int find(int n){
    return find0(n,0,FALSE);
}
int find0(int n, int current,bool is_update){
    // todo
    if(node_empty(current)) {
        if(is_update) node_data_set(current,n);
        return -1;
    }

    if( node_data_get(current) == n){
        return current;
    }else if(n < curent.data){
        // in left
        return find0(n, node_left(current))
    }else{
        // in right
        return find0(n, node_right(current))
    }
}

int add(int n){
    return find0(n,0,TRUE);
}
