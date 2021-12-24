#include <stdio.h>
#include <string.h>

int main(){
    char* a[3][2] = {
        {"123","345"},
        {"123","nihoa"},
        {"345","nihoa"}
    };
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            printf(" %s",a[i][j]);
        }
        printf("\n");
    }

	char msg[] = "1234";
    printf("%d\n",sizeof(msg));

}
