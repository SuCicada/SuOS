#include "utils.h"

// #define between(n,a,b) n>a

// ===== su_sprintf ===========
char temp_str[20];

int int2hexstr(int n, char *s);

int int2basestr(int n, char *s, int base);

int int2basestr0(int n, char *s, int base, int is_u);

int su_sprintf(char *_stream, char *_format, ...) {
    char c;
    char *stream = _stream;
    char *arg = (char *) (&_format + 1);
    // printf("arg %d\n",*(int*)arg);
    int n;
    int match_num_len; // len of % match num

    while ((c = *(_format++)) != 0) {
        // printf("c %c\n",c);
        // printf("s %s\n",__stream);
        if (c == '%') {
            // prepare get next char
            char c1 = *(_format);
            char c2 = *(_format + 1);

            int prefix_size = 0;
            char prefix_char = ' ';
            if (charIsNum(c2)) {
                /* eg: %03d , %-3d */
                // __format++;
                // char cc = *(__format + 1);
                // if (charIsNum(c1)) {
                prefix_char = c1;
                prefix_size = char2Num(c2);
                _format += 2;
                // __format++;
            } else if (charIsNum(c1)) {
                /* eg: %3d */
                prefix_size = char2Num(c1);
                _format++;
            }

            c = *(_format++);
            int is_num_flag = 0;
            switch (c) {
                case 'x':
                    n = *(int *) arg;
                    printf("xxxx %d\n",n);
                    arg += sizeof(int);
                    is_num_flag = 1;
                    match_num_len = int2hexstr(n, temp_str);
                    break;
                case 'd':
                    n = *(int *) arg;
                    arg += sizeof(int);
                    is_num_flag = 1;
                    match_num_len = int2str(n, temp_str);
                    break;
                case 'u':
                    n = *(int *) arg;
                    arg += sizeof(int);
                    is_num_flag = 1;
                    match_num_len = uint2str((unsigned int) n, temp_str);
                    break;
                case '%':
                    *(stream++) = '%';
                    break;
                default:
                    break;
            }
            if (is_num_flag == 1) {
                // 填补数字前缀
                if (match_num_len < prefix_size) {
                    for (int i = 0; i < prefix_size - match_num_len; i++) {
                        *(stream++) = prefix_char;
                    }
                }
                for (int i = 0; i < match_num_len; i++) {
                    *(stream++) = temp_str[i];
                }
            }
        } else {
            *(stream++) = c;
        }
        // __format++;
    }
    *stream = '\0';
    return 0;
}

int int2str(int n, char *s) {
    int flag_size = 0;
    if (n < 0) {
        *(s++) = '-';
        n = -n;
        flag_size = 1;
    }
    return int2basestr(n, s, 10) + flag_size;
}

int uint2str(unsigned int n, char *s) {
    return int2basestr0(n, s, 10, 1);
}

int basechar2int(char c) {
    if (charIsNum(c)) return c - '0';
    else return c - 'a' + 10;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

char int2basechar(int n) {
    if (n < 10) return '0' + n;
    else return 'a' + n - 10;
}

int int2hexstr(int n, char *s) {
    if (n < 0) {
        n = 0x7fffffff + n + 1;
        // n = 1<<32
    }
    int res = int2basestr(n, s, 16);
    // 最高位设置为 1
    s[0] = int2basechar(basechar2int(s[0]) + 8);
    return res;
}


int int2basestr(int n, char *s, int base) {
    return int2basestr0(n, s, base, 0);
}

/*
    base: 10 / 16 进制
    is_u: bool 是否为无符号
 */
int int2basestr0(int n, char *s, int base, int is_u) {
    int flag = 0;
    do {
        int rem;
        if (is_u) rem = (unsigned int) n % base;
        else rem = n % base;

        char c = int2basechar(rem);
        s[flag++] = c;
        n /= base;
    } while (n);
    char c;
    for (int i = 0; i < flag / 2; i++) {
        c = s[i];
        s[i] = s[flag - i - 1];
        s[flag - i - 1] = c;
    }
    // s[flag] = '\0';
    return flag;
}


#pragma clang diagnostic pop
