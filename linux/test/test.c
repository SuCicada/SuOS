#include <stdio.h>

int com(int a, int b) {
    return a - b;
}

int invoke(void *fun) {

}

int main() {
    int aa = 143;
    void *a = &aa;
    int n = *(int *) a;
    int *nn = (int *) a + 1;
    printf("%p\n", a);
    printf("%d\n", n);
    printf("%p\n", nn);
    printf("%p\n", a + 1);
    int (*p)(int, int) = &com;
    int res = p(1, 22);
    printf("%d\n", res);
}
/*
stdiof
 sdfasdf
 sdf

*/
