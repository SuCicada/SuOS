//
// Created by SuCicada on 2/14/2022.
//

#include "../kernel/src/rbtree/rbtree.c"
#include <stdio.h>

int arr[];

void show() {
    for (int i = 0; i < 10; i++)
        printf("%2d |", i);
    printf("\n");
    for (int i = 0; i < 10; i++)
        printf("%2d |", arr[i]);
    printf("\n");
}

int main() {
    int need_add[] = {
            2,
            1,
            3,
            4
    };
    for (int i = 0; i < sizeof(need_add) / sizeof(int); i++) {
        add(need_add[i]);
    }
    show();
    int res = find(2);
    printf("res %d\n", res);
}
