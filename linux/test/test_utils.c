#include <stdio.h>
#include "../kernel/utils.c"
#include <unistd.h>

// #define sprintf sprintf
char s[100];
int main() {
    // sleep(1);
    int len;
    
    sprintf(s,"nihoa: %d - %1d %05d|",123, 45,6789); 
    printf("%s|\n", s);
    su_sprintf(s,"nihoa: %d - %1d %05d|",123, 45,6789); 
    printf("%s|\n", s);
    // sprintf(s,"nihoa: %x - %x %03x|",0x123, 0xa,0xb); 
    // printf("%s|\n", s);
    // su_sprintf(s,"nihoa: |"); 
    printf("=====\n");
    return 0;

}
