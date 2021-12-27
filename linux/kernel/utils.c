int int2str(int n, char* s);
int su_sprintf(char* __stream, char* __format, ...) {
    char c;
    char* stream = __stream;
    char* arg = (char*)(&__format + 1);
    // printf("arg %d\n",*(int*)arg);
    int n;
    while ((c = *__format) && c!=0) {
        // printf("c %c\n",c);
        // printf("s %s\n",__stream);
        if (c == '%') {
            __format++;
            c = *__format;
            switch (c) {
            case 'd':
                n = *(int*)arg;
                // printf("n /%d\n",n);
                // printf("n %d\n",*(arg+8));
                arg += sizeof(int);
                int len = int2str(n, stream);
                stream += len;
                break;
            }
        }
        else {
            *stream = c;
            stream++;
        }
        __format++;
    }
    *stream = '\0';
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