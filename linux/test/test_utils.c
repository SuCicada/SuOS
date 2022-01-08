#include <stdio.h>
#include "../kernel/utils.c"
#include <unistd.h>
int main() {
    sleep(1);
    char s[100];
    int len;

    su_sprintf(s,"nihoa: %d - %d %d|",123, 45,6789); 
    printf("%s|\n", s);
    su_sprintf(s,"nihoa: %x - %x %x|",0x123, 0xa,0xb); 
    printf("%s|\n", s);
    // su_sprintf(s,"nihoa: |"); 
    printf("=====\n");
    return 0;

}
