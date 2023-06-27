//
// Created by SuCicada on 2023/06/13.
//
#include "serial.h"
#include "utils.h"
#include "log.h"

char log_tmp_string[128];

void log_println(char *_format, ...) {
    char *arg = (char *) (&_format + 1);
//    log_info(_format, *arg);
    su_sprintf_ptr(log_tmp_string, _format,arg);
    write_serial_string(log_tmp_string);
    write_serial_string("\n");
}

void log_info(char *_format, ...) {
    char *arg = (char *) (&_format + 1);
//    if(*arg){
    su_sprintf_ptr(log_tmp_string, _format, arg);
    write_serial_string(log_tmp_string);
//    }else{
//        write_serial_string(_format);
//    }
}

void debug(char *_format, ...){}
