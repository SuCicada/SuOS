#ifndef SUOS_utils_H
#define SUOS_utils_H

int int2str(int n, char *s);

int uint2str(unsigned int n, char *s);

#define charIsNum(c) ((c) >= '0' && (c) <= '9')
#define char2Num(c) ((c) - '0')

int su_sprintf(char *_stream, char *_format, ...);


#endif //SUOS_utils_H
