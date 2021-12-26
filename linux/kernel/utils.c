int int2str(int n, char* s);
int su_sprintf(char* __stream, char* __format, ...) {
    char c;
    char* stream = __stream;
    char* arg = (char*)(&__format + sizeof(char*));
    // printf("arg %d\n",*(int*)arg);
    int n;
    while ((c = *__format) && c) {
        // printf("c %c\n",c);
        // printf("s %s\n",__stream);
        if(c == '%'){

        }else if (*(__format - 1) == '%') {
            switch (c) {
            case 'd':
                n = *(int*)arg;
                arg += sizeof(int);
                int len = int2str(n, stream);
                // printf("len %d\n",n);
                stream += len;
                break;
            }
        }else{
                *stream = c;
                stream++;
        }
        *stream = '\0';
        __format++;
    }
    return 0;
}

int int2str(int n, char* s) {
    int flag = 0;
    do {
        s[flag++] = '0' + n % 10;
        n /= 10;
    } while (n);
    char c;
    for (int i = 0;i < flag / 2;i++) {
        c = s[i];
        s[i] = s[flag - i - 1];
        s[flag - i - 1] = c;
    }
    // s[flag] = '\0';
    return flag;
}