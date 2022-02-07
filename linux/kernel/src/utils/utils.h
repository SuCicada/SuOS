int int2str(int n, char* s);
int int2hexstr(int n, char* s);
int int2basestr(int n, char* s, int base);

#define charIsNum(c) (c >= '0' && c <= '9')
#define char2Num(c) (c - '0')

int su_sprintf(char* __stream, char* __format, ...);

