#include "header.h"
int int2str(int n, char* s);
int int2hexstr(int n, char* s);
int int2basestr(int n, char* s, int base);

#define charIsNum(c) (c >= '0' && c <= '9')
#define char2Num(c) (c - '0')

char temp_str[20];
int su_sprintf(char* __stream, char* __format, ...) {
    char c;
    char* stream = __stream;
    char* arg = (char*)(&__format + 1);
    // printf("arg %d\n",*(int*)arg);
    int n;
    int match_num_len; // len of % match num 

    while ((c = *(__format++)) && c != 0) {
        // printf("c %c\n",c);
        // printf("s %s\n",__stream);
        if (c == '%') {
            // prepare get next char
            char c1 = *(__format);
            char c2 = *(__format + 1);

            int prefix_size = 0;
            int prefix_char = ' ';
            if (charIsNum(c2)) {
                // eg: %03d , %-3d
                // __format++;
                // char cc = *(__format + 1);
                // if (charIsNum(c1)) {
                prefix_char = c1;
                prefix_size = char2Num(c2);
                __format += 2;
                // __format++;
            }
            else if (charIsNum(c1)) {
                // eg: %3d
                prefix_size = char2Num(c1);
                __format++;
            }

            c = *(__format++);
            switch (c) {
            case 'x':
            case 'd':
                n = *(int*)arg;
                arg += sizeof(int);
                switch (c) {
                case 'd': match_num_len = int2str(n, temp_str); break;
                case 'x': match_num_len = int2hexstr(n, temp_str); break;
                }
                // 填补数字前缀
                if (match_num_len < prefix_size) {
                    for (int i = 0;i < prefix_size - match_num_len;i++) {
                        *(stream++) = prefix_char;
                    }
                }
                for (int i = 0;i < match_num_len;i++) {
                    *(stream++) = temp_str[i];
                }
                break;
            case '%':
                *(stream++) = '%';
                break;
            }
        }
        else {
            *(stream++) = c;
        }
        // __format++;
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
