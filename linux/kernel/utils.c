#include "header.h"
int int2str(int n, char* s);
int int2hexstr(int n, char* s);
int int2basestr(int n, char* s, int base);

int su_sprintf(char* __stream, char* __format, ...) {
    char c;
    char* stream = __stream;
    char* arg = (char*)(&__format + 1);
    // printf("arg %d\n",*(int*)arg);
    int n;
    int len;
    while ((c = *__format) && c != 0) {
        // printf("c %c\n",c);
        // printf("s %s\n",__stream);
        if (c == '%') {
            __format++;
            c = *__format;
            switch (c) {
            case 'd':
                n = *(int*)arg;
                arg += sizeof(int);
                len = int2str(n, stream);
                stream += len;
                break;
            case 'x':
                n = *(int*)arg;
                arg += sizeof(int);
                len = int2hexstr(n, stream);
                stream += len;
                break;
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
    return int2basestr(n, s, 10);
}
int int2hexstr(int n, char* s) {
    return int2basestr(n, s, 16);
}

int int2basestr(int n, char* s, int base) {
    int flag = 0;
    do {
        int rem = n % base;
        int c;
        if (rem < 10) {
            c = '0' + rem;
        }
        else {
            c = 'a' + rem - 10;
        }
        s[flag++] = c;
        n /= base;
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
