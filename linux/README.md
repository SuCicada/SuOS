```bash
apt install nasm
apt install gcc-multilib


make debug_build=true -B
```

https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html


<pre>
floppy.nas 已经没有用了

一张软盘 80柱面 2个磁头 18扇区 一个扇区512B
一共 1474560 B

0x007c00 : suos 开始读取 10*2*18*512B = 180KB
0x007c00 -- 0x007dff : 启动区内容装载区域,即磁盘第一个扇区 (512 B)
0x008000 -- 0x0081ff : 大小为 512, 貌似空下了, 是为了对齐第一个扇区
0x008200 -- 0x034fff : 读取磁盘 10*2*18*512B - 512 = 180KB - 512


(针对于img文件) 0x4400: kernerl所在的起始地址

0xc400 : 是通过挂载方式写入kernerl文件后
         (针对于拷贝到内存) 0x4400 + 0x8000 = 0xc400


0x00000000 -- 0x000fffff : seg 2, entry code (1 MB)
0x00100000 -- 0x0026f7ff : (1470 KB)
0x0026f800 -- 0x0026ffff : 设置为 IDT (2 KB)
0x00270000 -- 0x0027ffff : 设置为 GDT, 这个地址可以随便指定 (64 KB)
0x00280000 -- 0x002fffff : seg 3, 把 kernel 拷贝到这里 (512 KB)(0x00080000 B) , 对应 entry 的 copy_main
0x00300000 -- 0x003fffff :

0x00400000 -- 0x0040d000 : 内存分配表

0x200 == 512
0x400 == 1024 == 2**10
0x100 == 2**(4+4)




</pre>
