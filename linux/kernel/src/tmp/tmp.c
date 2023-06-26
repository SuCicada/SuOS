//
// Created by Pengyifu on 2023/06/05.
//
#include "color.h"
#include "screen.h"
void make_window8(unsigned char *buf,int xsize,int ysize,char *title)
{
    static char closebtn[14][16] = {
            "OOOOOOOOOOOOOOO@",
            "OQQQQQQQQQQQQQ$@",
            "OQQQQQQQQQQQQQ$@",
            "OQQQ@@QQQQ@@QQ$@",
            "OQQQQ@@QQ@@QQQ$@",
            "OQQQQQ@@@@QQQQ$@",
            "OQQQQQQ@@QQQQQ$@",
            "OQQQQQ@@@@QQQQ$@",
            "OQQQQ@@QQ@@QQQ$@",
            "OQQQ@@QQQQ@@QQ$@",
            "OQQQQQQQQQQQQQ$@",
            "OQQQQQQQQQQQQQ$@",
            "O$$$$$$$$$$$$$$@",
            "@@@@@@@@@@@@@@@@"
    };

    int x,y;
    char c;
    boxfill8(buf, xsize, 8, 0, 0, xsize - 1, 0);
    boxfill8(buf, xsize, 7, 1, 1, xsize - 2, 1);
    boxfill8(buf, xsize, 8, 0, 0, 0, ysize - 1);
    boxfill8(buf, xsize, 7, 1, 1, 1, ysize - 2);
    boxfill8(buf, xsize, 15, xsize - 2, 1, xsize - 2, ysize - 2);
    boxfill8(buf, xsize, 0, xsize - 1, 0, xsize - 1, ysize - 1);
    boxfill8(buf, xsize, 8, 2, 2, xsize - 3, ysize - 3);
    boxfill8(buf, xsize, 12, 3, 3, xsize - 4, 20);
    boxfill8(buf, xsize, 15, 1, ysize - 2, xsize - 2, ysize - 2);
//    boxfill8_v1(buf, xsize, 0, 0, ysize - 1, xsize - 1, ysize - 1);


    puts8(buf,xsize,24,4,7,title);
    //write the x button to the buf
    for(y=0;y<14;y++)
    {
        for(x=0;x<16;x++)
        {
            c=closebtn[y][x];
            if(c=='@')
                c=0;
            else if(c=='$')
                c=15;
            else if(c=='Q')
                c=8;
            else c=7;
        }
        buf[(5+y)*xsize+(xsize-21+x)]=c;


    }
    return;




}
