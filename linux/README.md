floppy.nas 已经没有用了
目前来说  screen.c 和 header.h 也没用

一张软盘 80柱面 2个磁头 18扇区 一个扇区512B
0x7c00   suos 开始读取 10*2*18*512B = 180KB

0xc400 是写入kernerl文件后, 读取磁盘后, kernerl所在的地址

0x00270000 -- 0x0027ffff : 设置为GDT, 这个地址可以随便指定

0x00280000 -- 0x002fffff : 把 kernel 拷贝到这里




