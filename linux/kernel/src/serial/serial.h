#ifndef SUOS_SERIAL_H
#define SUOS_SERIAL_H

#define COM1_PORT 0x3f8          // COM1

int init_serial();
void write_serial(char a);
void write_serial_string(char* str);


#endif //SUOS_SERIAL_H
