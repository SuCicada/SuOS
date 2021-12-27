#include <stdio.h>
#include "../kernel/utils.c"
int main() {
    char s[100];
    int len;

    su_sprintf(s,"nihoa: %d - %d %d|",123, 45,6789); 
    // su_sprintf(s,"nihoa: |"); 
    printf("%s|\n|", s);
    printf("=====\n");
    return 0;

}
