//
// Created by SuCicada on 2023/06/22.
//
//
// Created by SuCicada on 2023/06/13.
//
#include <stdarg.h>
#include "log.h"
#include "stdio.h"

void log_println(char *_format, ...) {
    va_list args;
    va_start(args, _format);
    vprintf(_format, args);
    printf("\n");
    va_end(args);
}

void log_info(char *_format, ...) {
    va_list args;
    va_start(args, _format);
    vprintf(_format, args);
    va_end(args);
}

void debug(char *_format, ...){
/* 可变参数宏来获取可变参数列表 */
    va_list args;
    va_start(args, _format);
    vprintf(_format, args);
    va_end(args);
//    printf(_format, &_format + 1);
}
