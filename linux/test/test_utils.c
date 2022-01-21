#include <stdio.h>
#include "../kernel/utils.c"
#include <unistd.h>

// #define sprintf sprintf
char s[100];
int main() {
    // sleep(1);
    int len;
    int a = -23;
    unsigned int n = 0x7fffffff + a+1;

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
    return 0;

}
