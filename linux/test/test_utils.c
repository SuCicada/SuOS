#include "../kernel/src/utils/utils.h"
#include "../kernel/src/utils/utils.c"
#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <resolv.h>

//extern int sprintf(char *__restrict __s,
//                   const char *__restrict __format, ...);

extern void *malloc(size_t __size);

// #define sprintf sprintf
char s[100];

void test_int2hexstr() {
    int n = 2634848;
    int res = int2hexstr(n, s);
    printf("%d %s|\n", res, s);
    printf("%d == 0x%x|\n", n, n);
}

int main() {
    // sleep(1);
    int len;
    int a = -23;
    unsigned int n = 0x7fffffff + a + 1;

//    su_sprintf(s, "%x|", 2634848,1,2);
    test_int2hexstr();
//    printf("%s|\n", s);
    return 0;
    sprintf(s, "nihoa: %d - %1x %05d|", a, a, 6789);
    printf("%s|\n", s);
    su_sprintf(s, "nihoa: %d - %1x %05d|", a, a, 6789);
    printf("%s|\n", s);
    // sprintf(s,"nihoa: %x - %x %03x|",0x123, 0xa,0xb);
    // printf("%s|\n", s);
    // su_sprintf(s,"nihoa: |");
    printf("=====\n");
    printf("%d\n", n);
    printf("%1x\n", n);
    unsigned int n1 = 0xffffffff;
    printf("%d %u\n", n1, n1);
    int *aa = malloc(12311232222323);
    return 0;

}
