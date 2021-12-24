
kernel.out:     file format elf32-i386


Disassembly of section .text:

0000c400 <init_palette>:
#define COL8_848484 15 // 暗い灰色

void set_palette(int start, int end, unsigned char *rgb_table);

void init_palette()
{
    c400:	f3 0f 1e fb          	endbr32 
    c404:	55                   	push   %ebp
    c405:	89 e5                	mov    %esp,%ebp
    c407:	83 ec 08             	sub    $0x8,%esp
    c40a:	e8 72 04 00 00       	call   c881 <__x86.get_pc_thunk.ax>
    c40f:	05 b5 06 00 00       	add    $0x6b5,%eax
    };
    // rgb_table[0]=0xff;
    // int a = rgb_table[2];
    // rgb_table[0 * 3 + 1] = 0xff;
    // rgb_table[0 * 3 + 2] = 0xff;
    set_palette(0, 15, rgb_table);
    c414:	83 ec 04             	sub    $0x4,%esp
    c417:	8d 80 3c 10 00 00    	lea    0x103c(%eax),%eax
    c41d:	50                   	push   %eax
    c41e:	6a 0f                	push   $0xf
    c420:	6a 00                	push   $0x0
    c422:	e8 06 00 00 00       	call   c42d <set_palette>
    c427:	83 c4 10             	add    $0x10,%esp
    return;
    c42a:	90                   	nop
    // static char 命令は、データにしか使えないけどDB命令担当
}
    c42b:	c9                   	leave  
    c42c:	c3                   	ret    

0000c42d <set_palette>:

void set_palette(int start, int end, unsigned char *rgb_table)
{
    c42d:	f3 0f 1e fb          	endbr32 
    c431:	55                   	push   %ebp
    c432:	89 e5                	mov    %esp,%ebp
    c434:	53                   	push   %ebx
    c435:	83 ec 14             	sub    $0x14,%esp
    c438:	e8 48 04 00 00       	call   c885 <__x86.get_pc_thunk.bx>
    c43d:	81 c3 87 06 00 00    	add    $0x687,%ebx
    // int start = 0,
    //     end = 15;
    int flag = io_read_eflags();
    c443:	e8 2e 05 00 00       	call   c976 <io_read_eflags>
    c448:	89 45 e8             	mov    %eax,-0x18(%ebp)
    io_cli();
    c44b:	e8 22 05 00 00       	call   c972 <io_cli>
    unsigned char *rgb_table_pnt = rgb_table;
    c450:	8b 45 10             	mov    0x10(%ebp),%eax
    c453:	89 45 f4             	mov    %eax,-0xc(%ebp)
    io_out8(0x03c8, start);
    c456:	83 ec 08             	sub    $0x8,%esp
    c459:	ff 75 08             	pushl  0x8(%ebp)
    c45c:	68 c8 03 00 00       	push   $0x3c8
    c461:	e8 25 05 00 00       	call   c98b <io_out8>
    c466:	83 c4 10             	add    $0x10,%esp

    for (int i = start; i <= end; i++)
    c469:	8b 45 08             	mov    0x8(%ebp),%eax
    c46c:	89 45 f0             	mov    %eax,-0x10(%ebp)
    c46f:	eb 3c                	jmp    c4ad <set_palette+0x80>
    {
        // io_out8(0x03c9, 0xff);
        // io_out8(0x03c9, 0x00);
        // io_out8(0x03c9, 0x00);
        for (int j = 0; j < 3; j++)
    c471:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
    c478:	eb 26                	jmp    c4a0 <set_palette+0x73>
        {
            io_out8(0x03c9, rgb_table_pnt[j] / 4);
    c47a:	8b 55 ec             	mov    -0x14(%ebp),%edx
    c47d:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c480:	01 d0                	add    %edx,%eax
    c482:	8a 00                	mov    (%eax),%al
    c484:	c0 e8 02             	shr    $0x2,%al
    c487:	25 ff 00 00 00       	and    $0xff,%eax
    c48c:	83 ec 08             	sub    $0x8,%esp
    c48f:	50                   	push   %eax
    c490:	68 c9 03 00 00       	push   $0x3c9
    c495:	e8 f1 04 00 00       	call   c98b <io_out8>
    c49a:	83 c4 10             	add    $0x10,%esp
        for (int j = 0; j < 3; j++)
    c49d:	ff 45 ec             	incl   -0x14(%ebp)
    c4a0:	83 7d ec 02          	cmpl   $0x2,-0x14(%ebp)
    c4a4:	7e d4                	jle    c47a <set_palette+0x4d>
            // io_out8(0x03c9, rgb_table[i * 3 + j] / 4);
            // rgb_table[j]
        }
        rgb_table_pnt += 3;
    c4a6:	83 45 f4 03          	addl   $0x3,-0xc(%ebp)
    for (int i = start; i <= end; i++)
    c4aa:	ff 45 f0             	incl   -0x10(%ebp)
    c4ad:	8b 45 f0             	mov    -0x10(%ebp),%eax
    c4b0:	3b 45 0c             	cmp    0xc(%ebp),%eax
    c4b3:	7e bc                	jle    c471 <set_palette+0x44>
    }
    io_store_eflags(flag);
    c4b5:	83 ec 0c             	sub    $0xc,%esp
    c4b8:	ff 75 e8             	pushl  -0x18(%ebp)
    c4bb:	e8 b9 04 00 00       	call   c979 <io_store_eflags>
    c4c0:	83 c4 10             	add    $0x10,%esp
    // io_sti();
    return;
    c4c3:	90                   	nop
}
    c4c4:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    c4c7:	c9                   	leave  
    c4c8:	c3                   	ret    

0000c4c9 <bootmain>:
void boxfill(int color_flag, int x0, int y0, int x1, int y1);
void init_screen();
void putfont(int x, int y, char color, char *font);

void bootmain(void)
{
    c4c9:	f3 0f 1e fb          	endbr32 
    c4cd:	55                   	push   %ebp
    c4ce:	89 e5                	mov    %esp,%ebp
    c4d0:	53                   	push   %ebx
    c4d1:	83 ec 14             	sub    $0x14,%esp
    c4d4:	e8 ac 03 00 00       	call   c885 <__x86.get_pc_thunk.bx>
    c4d9:	81 c3 eb 05 00 00    	add    $0x5eb,%ebx
	struct BootInfo *binfo = (struct BootInfo *)0x0ff0;
    c4df:	c7 45 f0 f0 0f 00 00 	movl   $0xff0,-0x10(%ebp)

	init_display_info(binfo);
    c4e6:	83 ec 0c             	sub    $0xc,%esp
    c4e9:	ff 75 f0             	pushl  -0x10(%ebp)
    c4ec:	e8 06 01 00 00       	call   c5f7 <init_display_info>
    c4f1:	83 c4 10             	add    $0x10,%esp
	init_palette();
    c4f4:	e8 07 ff ff ff       	call   c400 <init_palette>
	init_screen();
    c4f9:	e8 99 01 00 00       	call   c697 <init_screen>
	static char font_A[16] = {
		0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
		0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00,
  	};
	static char msg[] = "I'm SuCicada.";
	for(int i=0;i<sizeof(msg)-1;i++){
    c4fe:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
    c505:	eb 44                	jmp    c54b <bootmain+0x82>
		int font = msg[i];
    c507:	8d 93 6c 10 00 00    	lea    0x106c(%ebx),%edx
    c50d:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c510:	01 d0                	add    %edx,%eax
    c512:	8a 00                	mov    (%eax),%al
    c514:	0f be c0             	movsbl %al,%eax
    c517:	89 45 ec             	mov    %eax,-0x14(%ebp)
		putfont(10*i+5, 10, COL8_FFFFFF, hankaku[font]);
    c51a:	8b 45 ec             	mov    -0x14(%ebp),%eax
    c51d:	c1 e0 04             	shl    $0x4,%eax
    c520:	89 c2                	mov    %eax,%edx
    c522:	8d 83 1c 00 00 00    	lea    0x1c(%ebx),%eax
    c528:	8d 0c 02             	lea    (%edx,%eax,1),%ecx
    c52b:	8b 55 f4             	mov    -0xc(%ebp),%edx
    c52e:	89 d0                	mov    %edx,%eax
    c530:	c1 e0 02             	shl    $0x2,%eax
    c533:	01 d0                	add    %edx,%eax
    c535:	01 c0                	add    %eax,%eax
    c537:	83 c0 05             	add    $0x5,%eax
    c53a:	51                   	push   %ecx
    c53b:	6a 07                	push   $0x7
    c53d:	6a 0a                	push   $0xa
    c53f:	50                   	push   %eax
    c540:	e8 15 00 00 00       	call   c55a <putfont>
    c545:	83 c4 10             	add    $0x10,%esp
	for(int i=0;i<sizeof(msg)-1;i++){
    c548:	ff 45 f4             	incl   -0xc(%ebp)
    c54b:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c54e:	83 f8 0c             	cmp    $0xc,%eax
    c551:	76 b4                	jbe    c507 <bootmain+0x3e>
	// 	write_mem8(i,15);
	// }
	// // while(1);
	for (;;)
	{
		io_hlt();
    c553:	e8 18 04 00 00       	call   c970 <io_hlt>
    c558:	eb f9                	jmp    c553 <bootmain+0x8a>

0000c55a <putfont>:
              //int xsize,    // 4 byte
              int x,        // 4 byte
              int y,        // 4 byte
              char color,       // 1 byte
              char *font)   // 4 byte
{
    c55a:	f3 0f 1e fb          	endbr32 
    c55e:	55                   	push   %ebp
    c55f:	89 e5                	mov    %esp,%ebp
    c561:	53                   	push   %ebx
    c562:	83 ec 24             	sub    $0x24,%esp
    c565:	e8 17 03 00 00       	call   c881 <__x86.get_pc_thunk.ax>
    c56a:	05 5a 05 00 00       	add    $0x55a,%eax
    c56f:	8b 55 10             	mov    0x10(%ebp),%edx
    c572:	88 55 d8             	mov    %dl,-0x28(%ebp)
  	int i;
  	char d;     // 1 byte
  	char *p;    // 4 byte
  	for (i = 0; i < 16; i++){
    c575:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%ebp)
    c57c:	eb 6c                	jmp    c5ea <putfont+0x90>
		// 左上を(0, 0)として(x, y)の座標に描画
		p = DISPLAY_ADDRE + (y + i) * DISPLAY_X_SIZE + x;   // 1 byte
    c57e:	8b 90 24 10 00 00    	mov    0x1024(%eax),%edx
    c584:	8b 5d 0c             	mov    0xc(%ebp),%ebx
    c587:	8b 4d f8             	mov    -0x8(%ebp),%ecx
    c58a:	01 cb                	add    %ecx,%ebx
    c58c:	8b 88 1c 10 00 00    	mov    0x101c(%eax),%ecx
    c592:	0f af cb             	imul   %ebx,%ecx
    c595:	89 cb                	mov    %ecx,%ebx
    c597:	8b 4d 08             	mov    0x8(%ebp),%ecx
    c59a:	01 d9                	add    %ebx,%ecx
    c59c:	01 ca                	add    %ecx,%edx
    c59e:	89 55 ec             	mov    %edx,-0x14(%ebp)
		d = font[i];
    c5a1:	8b 4d f8             	mov    -0x8(%ebp),%ecx
    c5a4:	8b 55 14             	mov    0x14(%ebp),%edx
    c5a7:	01 ca                	add    %ecx,%edx
    c5a9:	8a 12                	mov    (%edx),%dl
    c5ab:	88 55 eb             	mov    %dl,-0x15(%ebp)
		unsigned char tmp=1<<7;
    c5ae:	c6 45 f7 80          	movb   $0x80,-0x9(%ebp)
		for(int j=0; j<8; j++,tmp>>=1){
    c5b2:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
    c5b9:	eb 26                	jmp    c5e1 <putfont+0x87>
			if ((d & tmp) != 0)
    c5bb:	0f be 4d eb          	movsbl -0x15(%ebp),%ecx
    c5bf:	8a 55 f7             	mov    -0x9(%ebp),%dl
    c5c2:	81 e2 ff 00 00 00    	and    $0xff,%edx
    c5c8:	21 ca                	and    %ecx,%edx
    c5ca:	85 d2                	test   %edx,%edx
    c5cc:	74 0d                	je     c5db <putfont+0x81>
				p[j] = color;
    c5ce:	8b 4d f0             	mov    -0x10(%ebp),%ecx
    c5d1:	8b 55 ec             	mov    -0x14(%ebp),%edx
    c5d4:	01 d1                	add    %edx,%ecx
    c5d6:	8a 55 d8             	mov    -0x28(%ebp),%dl
    c5d9:	88 11                	mov    %dl,(%ecx)
		for(int j=0; j<8; j++,tmp>>=1){
    c5db:	ff 45 f0             	incl   -0x10(%ebp)
    c5de:	d0 6d f7             	shrb   -0x9(%ebp)
    c5e1:	83 7d f0 07          	cmpl   $0x7,-0x10(%ebp)
    c5e5:	7e d4                	jle    c5bb <putfont+0x61>
  	for (i = 0; i < 16; i++){
    c5e7:	ff 45 f8             	incl   -0x8(%ebp)
    c5ea:	83 7d f8 0f          	cmpl   $0xf,-0x8(%ebp)
    c5ee:	7e 8e                	jle    c57e <putfont+0x24>
		}
	}
  	return;
    c5f0:	90                   	nop
}
    c5f1:	83 c4 24             	add    $0x24,%esp
    c5f4:	5b                   	pop    %ebx
    c5f5:	5d                   	pop    %ebp
    c5f6:	c3                   	ret    

0000c5f7 <init_display_info>:

void init_display_info(struct BootInfo *binfo)
{
    c5f7:	f3 0f 1e fb          	endbr32 
    c5fb:	55                   	push   %ebp
    c5fc:	89 e5                	mov    %esp,%ebp
    c5fe:	e8 7e 02 00 00       	call   c881 <__x86.get_pc_thunk.ax>
    c603:	05 c1 04 00 00       	add    $0x4c1,%eax
	DISPLAY_ADDRE = binfo->vram;
    c608:	8b 55 08             	mov    0x8(%ebp),%edx
    c60b:	8b 52 08             	mov    0x8(%edx),%edx
    c60e:	89 90 24 10 00 00    	mov    %edx,0x1024(%eax)
	DISPLAY_X_SIZE = binfo->scrnx,
    c614:	8b 55 08             	mov    0x8(%ebp),%edx
    c617:	8b 52 04             	mov    0x4(%edx),%edx
    c61a:	0f bf d2             	movswl %dx,%edx
    c61d:	89 90 1c 10 00 00    	mov    %edx,0x101c(%eax)
	DISPLAY_Y_SIZE = binfo->scrny;
    c623:	8b 55 08             	mov    0x8(%ebp),%edx
    c626:	66 8b 52 06          	mov    0x6(%edx),%dx
    c62a:	0f bf d2             	movswl %dx,%edx
    c62d:	89 90 20 10 00 00    	mov    %edx,0x1020(%eax)
}
    c633:	90                   	nop
    c634:	5d                   	pop    %ebp
    c635:	c3                   	ret    

0000c636 <boxfill>:
void boxfill(int color_flag, int x0, int y0, int x1, int y1)
{
    c636:	f3 0f 1e fb          	endbr32 
    c63a:	55                   	push   %ebp
    c63b:	89 e5                	mov    %esp,%ebp
    c63d:	53                   	push   %ebx
    c63e:	83 ec 10             	sub    $0x10,%esp
    c641:	e8 3b 02 00 00       	call   c881 <__x86.get_pc_thunk.ax>
    c646:	05 7e 04 00 00       	add    $0x47e,%eax
	for (int y = y0; y <= y1; y++)
    c64b:	8b 55 10             	mov    0x10(%ebp),%edx
    c64e:	89 55 f8             	mov    %edx,-0x8(%ebp)
    c651:	eb 34                	jmp    c687 <boxfill+0x51>
		for (int x = x0; x <= x1; x++)
    c653:	8b 55 0c             	mov    0xc(%ebp),%edx
    c656:	89 55 f4             	mov    %edx,-0xc(%ebp)
    c659:	eb 21                	jmp    c67c <boxfill+0x46>
			((char *)DISPLAY_ADDRE)[y * DISPLAY_X_SIZE + x] = color_flag;
    c65b:	8b 88 24 10 00 00    	mov    0x1024(%eax),%ecx
    c661:	8b 90 1c 10 00 00    	mov    0x101c(%eax),%edx
    c667:	89 d3                	mov    %edx,%ebx
    c669:	0f af 5d f8          	imul   -0x8(%ebp),%ebx
    c66d:	8b 55 f4             	mov    -0xc(%ebp),%edx
    c670:	01 da                	add    %ebx,%edx
    c672:	01 ca                	add    %ecx,%edx
    c674:	8b 4d 08             	mov    0x8(%ebp),%ecx
    c677:	88 0a                	mov    %cl,(%edx)
		for (int x = x0; x <= x1; x++)
    c679:	ff 45 f4             	incl   -0xc(%ebp)
    c67c:	8b 55 f4             	mov    -0xc(%ebp),%edx
    c67f:	3b 55 14             	cmp    0x14(%ebp),%edx
    c682:	7e d7                	jle    c65b <boxfill+0x25>
	for (int y = y0; y <= y1; y++)
    c684:	ff 45 f8             	incl   -0x8(%ebp)
    c687:	8b 55 f8             	mov    -0x8(%ebp),%edx
    c68a:	3b 55 18             	cmp    0x18(%ebp),%edx
    c68d:	7e c4                	jle    c653 <boxfill+0x1d>
}
    c68f:	90                   	nop
    c690:	90                   	nop
    c691:	83 c4 10             	add    $0x10,%esp
    c694:	5b                   	pop    %ebx
    c695:	5d                   	pop    %ebp
    c696:	c3                   	ret    

0000c697 <init_screen>:

void init_screen()
{
    c697:	f3 0f 1e fb          	endbr32 
    c69b:	55                   	push   %ebp
    c69c:	89 e5                	mov    %esp,%ebp
    c69e:	53                   	push   %ebx
    c69f:	83 ec 10             	sub    $0x10,%esp
    c6a2:	e8 da 01 00 00       	call   c881 <__x86.get_pc_thunk.ax>
    c6a7:	05 1d 04 00 00       	add    $0x41d,%eax
	int xsize = DISPLAY_X_SIZE, ysize = DISPLAY_Y_SIZE;
    c6ac:	8b 90 1c 10 00 00    	mov    0x101c(%eax),%edx
    c6b2:	89 55 f8             	mov    %edx,-0x8(%ebp)
    c6b5:	8b 80 20 10 00 00    	mov    0x1020(%eax),%eax
    c6bb:	89 45 f4             	mov    %eax,-0xc(%ebp)
	boxfill(COL8_008484, 0, 0, xsize - 1, ysize - 29);
    c6be:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c6c1:	8d 50 e3             	lea    -0x1d(%eax),%edx
    c6c4:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c6c7:	48                   	dec    %eax
    c6c8:	52                   	push   %edx
    c6c9:	50                   	push   %eax
    c6ca:	6a 00                	push   $0x0
    c6cc:	6a 00                	push   $0x0
    c6ce:	6a 0e                	push   $0xe
    c6d0:	e8 61 ff ff ff       	call   c636 <boxfill>
    c6d5:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_C6C6C6, 0, ysize - 28, xsize - 1, ysize - 28);
    c6d8:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c6db:	8d 48 e4             	lea    -0x1c(%eax),%ecx
    c6de:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c6e1:	8d 50 ff             	lea    -0x1(%eax),%edx
    c6e4:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c6e7:	83 e8 1c             	sub    $0x1c,%eax
    c6ea:	51                   	push   %ecx
    c6eb:	52                   	push   %edx
    c6ec:	50                   	push   %eax
    c6ed:	6a 00                	push   $0x0
    c6ef:	6a 08                	push   $0x8
    c6f1:	e8 40 ff ff ff       	call   c636 <boxfill>
    c6f6:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_FFFFFF, 0, ysize - 27, xsize - 1, ysize - 27);
    c6f9:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c6fc:	8d 48 e5             	lea    -0x1b(%eax),%ecx
    c6ff:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c702:	8d 50 ff             	lea    -0x1(%eax),%edx
    c705:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c708:	83 e8 1b             	sub    $0x1b,%eax
    c70b:	51                   	push   %ecx
    c70c:	52                   	push   %edx
    c70d:	50                   	push   %eax
    c70e:	6a 00                	push   $0x0
    c710:	6a 07                	push   $0x7
    c712:	e8 1f ff ff ff       	call   c636 <boxfill>
    c717:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_C6C6C6, 0, ysize - 26, xsize - 1, ysize - 1);
    c71a:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c71d:	8d 48 ff             	lea    -0x1(%eax),%ecx
    c720:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c723:	8d 50 ff             	lea    -0x1(%eax),%edx
    c726:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c729:	83 e8 1a             	sub    $0x1a,%eax
    c72c:	51                   	push   %ecx
    c72d:	52                   	push   %edx
    c72e:	50                   	push   %eax
    c72f:	6a 00                	push   $0x0
    c731:	6a 08                	push   $0x8
    c733:	e8 fe fe ff ff       	call   c636 <boxfill>
    c738:	83 c4 14             	add    $0x14,%esp

	boxfill(COL8_FFFFFF, 3, ysize - 24, 59, ysize - 24);
    c73b:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c73e:	8d 50 e8             	lea    -0x18(%eax),%edx
    c741:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c744:	83 e8 18             	sub    $0x18,%eax
    c747:	52                   	push   %edx
    c748:	6a 3b                	push   $0x3b
    c74a:	50                   	push   %eax
    c74b:	6a 03                	push   $0x3
    c74d:	6a 07                	push   $0x7
    c74f:	e8 e2 fe ff ff       	call   c636 <boxfill>
    c754:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_FFFFFF, 2, ysize - 24, 2, ysize - 4);
    c757:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c75a:	8d 50 fc             	lea    -0x4(%eax),%edx
    c75d:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c760:	83 e8 18             	sub    $0x18,%eax
    c763:	52                   	push   %edx
    c764:	6a 02                	push   $0x2
    c766:	50                   	push   %eax
    c767:	6a 02                	push   $0x2
    c769:	6a 07                	push   $0x7
    c76b:	e8 c6 fe ff ff       	call   c636 <boxfill>
    c770:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_848484, 3, ysize - 4, 59, ysize - 4);
    c773:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c776:	8d 50 fc             	lea    -0x4(%eax),%edx
    c779:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c77c:	83 e8 04             	sub    $0x4,%eax
    c77f:	52                   	push   %edx
    c780:	6a 3b                	push   $0x3b
    c782:	50                   	push   %eax
    c783:	6a 03                	push   $0x3
    c785:	6a 0f                	push   $0xf
    c787:	e8 aa fe ff ff       	call   c636 <boxfill>
    c78c:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_848484, 59, ysize - 23, 59, ysize - 5);
    c78f:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c792:	8d 50 fb             	lea    -0x5(%eax),%edx
    c795:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c798:	83 e8 17             	sub    $0x17,%eax
    c79b:	52                   	push   %edx
    c79c:	6a 3b                	push   $0x3b
    c79e:	50                   	push   %eax
    c79f:	6a 3b                	push   $0x3b
    c7a1:	6a 0f                	push   $0xf
    c7a3:	e8 8e fe ff ff       	call   c636 <boxfill>
    c7a8:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_000000, 2, ysize - 3, 59, ysize - 3);
    c7ab:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c7ae:	8d 50 fd             	lea    -0x3(%eax),%edx
    c7b1:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c7b4:	83 e8 03             	sub    $0x3,%eax
    c7b7:	52                   	push   %edx
    c7b8:	6a 3b                	push   $0x3b
    c7ba:	50                   	push   %eax
    c7bb:	6a 02                	push   $0x2
    c7bd:	6a 00                	push   $0x0
    c7bf:	e8 72 fe ff ff       	call   c636 <boxfill>
    c7c4:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_000000, 60, ysize - 24, 60, ysize - 3);
    c7c7:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c7ca:	8d 50 fd             	lea    -0x3(%eax),%edx
    c7cd:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c7d0:	83 e8 18             	sub    $0x18,%eax
    c7d3:	52                   	push   %edx
    c7d4:	6a 3c                	push   $0x3c
    c7d6:	50                   	push   %eax
    c7d7:	6a 3c                	push   $0x3c
    c7d9:	6a 00                	push   $0x0
    c7db:	e8 56 fe ff ff       	call   c636 <boxfill>
    c7e0:	83 c4 14             	add    $0x14,%esp

	boxfill(COL8_848484, xsize - 47, ysize - 24, xsize - 4, ysize - 24);
    c7e3:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c7e6:	8d 58 e8             	lea    -0x18(%eax),%ebx
    c7e9:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c7ec:	8d 48 fc             	lea    -0x4(%eax),%ecx
    c7ef:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c7f2:	8d 50 e8             	lea    -0x18(%eax),%edx
    c7f5:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c7f8:	83 e8 2f             	sub    $0x2f,%eax
    c7fb:	53                   	push   %ebx
    c7fc:	51                   	push   %ecx
    c7fd:	52                   	push   %edx
    c7fe:	50                   	push   %eax
    c7ff:	6a 0f                	push   $0xf
    c801:	e8 30 fe ff ff       	call   c636 <boxfill>
    c806:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize - 4);
    c809:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c80c:	8d 58 fc             	lea    -0x4(%eax),%ebx
    c80f:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c812:	8d 48 d1             	lea    -0x2f(%eax),%ecx
    c815:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c818:	8d 50 e9             	lea    -0x17(%eax),%edx
    c81b:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c81e:	83 e8 2f             	sub    $0x2f,%eax
    c821:	53                   	push   %ebx
    c822:	51                   	push   %ecx
    c823:	52                   	push   %edx
    c824:	50                   	push   %eax
    c825:	6a 0f                	push   $0xf
    c827:	e8 0a fe ff ff       	call   c636 <boxfill>
    c82c:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_FFFFFF, xsize - 47, ysize - 3, xsize - 4, ysize - 3);
    c82f:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c832:	8d 58 fd             	lea    -0x3(%eax),%ebx
    c835:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c838:	8d 48 fc             	lea    -0x4(%eax),%ecx
    c83b:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c83e:	8d 50 fd             	lea    -0x3(%eax),%edx
    c841:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c844:	83 e8 2f             	sub    $0x2f,%eax
    c847:	53                   	push   %ebx
    c848:	51                   	push   %ecx
    c849:	52                   	push   %edx
    c84a:	50                   	push   %eax
    c84b:	6a 07                	push   $0x7
    c84d:	e8 e4 fd ff ff       	call   c636 <boxfill>
    c852:	83 c4 14             	add    $0x14,%esp
	boxfill(COL8_FFFFFF, xsize - 3, ysize - 24, xsize - 3, ysize - 3);
    c855:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c858:	8d 58 fd             	lea    -0x3(%eax),%ebx
    c85b:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c85e:	8d 48 fd             	lea    -0x3(%eax),%ecx
    c861:	8b 45 f4             	mov    -0xc(%ebp),%eax
    c864:	8d 50 e8             	lea    -0x18(%eax),%edx
    c867:	8b 45 f8             	mov    -0x8(%ebp),%eax
    c86a:	83 e8 03             	sub    $0x3,%eax
    c86d:	53                   	push   %ebx
    c86e:	51                   	push   %ecx
    c86f:	52                   	push   %edx
    c870:	50                   	push   %eax
    c871:	6a 07                	push   $0x7
    c873:	e8 be fd ff ff       	call   c636 <boxfill>
    c878:	83 c4 14             	add    $0x14,%esp
}
    c87b:	90                   	nop
    c87c:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    c87f:	c9                   	leave  
    c880:	c3                   	ret    

0000c881 <__x86.get_pc_thunk.ax>:
    c881:	8b 04 24             	mov    (%esp),%eax
    c884:	c3                   	ret    

0000c885 <__x86.get_pc_thunk.bx>:
    c885:	8b 1c 24             	mov    (%esp),%ebx
    c888:	c3                   	ret    
    c889:	66 90                	xchg   %ax,%ax
    c88b:	90                   	nop

0000c88c <start>:
.globl start
start:
  .code16                     # Assemble for 16-bit mode

  # Set up the important data segment registers (DS, ES, SS).
  xorw    %ax,%ax             # Segment number zero
    c88c:	31 c0                	xor    %eax,%eax
  movw    %ax,%ds             # -> Data Segment
    c88e:	8e d8                	mov    %eax,%ds
  movw    %ax,%es             # -> Extra Segment
    c890:	8e c0                	mov    %eax,%es
  movw    %ax,%ss             # -> Stack Segment
    c892:	8e d0                	mov    %eax,%ss
  
  movb $0x13,%al  # ;vga 320x200x8 位,color mode 
    c894:	b0 13                	mov    $0x13,%al
  movb $0x00,%ah
    c896:	b4 00                	mov    $0x0,%ah
  int $0x10
    c898:	cd 10                	int    $0x10
  
  # save color mode in ram 0x0ff0
  movb $8,(VMODE)
    c89a:	c6 06 f2             	movb   $0xf2,(%esi)
    c89d:	0f 08                	invd   
  movw $320,(SCRNX)
    c89f:	c7 06 f4 0f 40 01    	movl   $0x1400ff4,(%esi)
  movw $200,(SCRNY)
    c8a5:	c7 06 f6 0f c8 00    	movl   $0xc80ff6,(%esi)
  movl $0x000a0000,(VRAM)
    c8ab:	66 c7 06 f8 0f       	movw   $0xff8,(%esi)
    c8b0:	00 00                	add    %al,(%eax)
    c8b2:	0a 00                	or     (%eax),%al
  
  # get keyboard led status
  movb	$0x02,%ah 
    c8b4:	b4 02                	mov    $0x2,%ah
  int     $0x16			# keyboard interrupts
    c8b6:	cd 16                	int    $0x16
  movb   %al,(LEDS)
    c8b8:	a2 f1 0f be f1       	mov    %al,0xf1be0ff1
		
# diplay something
  movw $msg,%si
    c8bd:	c8 e8 5d 00          	enter  $0x5de8,$0x0
  call puts
  
  movw $try,%si
    c8c1:	be 0d c9 e8 57       	mov    $0x57e8c90d,%esi
  call puts
    c8c6:	00 fa                	add    %bh,%dl
  
  # jmp .
   cli                         # Disable interrupts
   cld                         # String operations increment
    c8c8:	fc                   	cld    

0000c8c9 <seta20.1>:
  # Enable A20:
  #   For backwards compatibility with the earliest PCs, physical
  #   address line 20 is tied low, so that addresses higher than
  #   1MB wrap around to zero by default.  This code undoes this. 
seta20.1:
  inb     $0x64,%al               # Wait for not busy
    c8c9:	e4 64                	in     $0x64,%al
  testb   $0x2,%al
    c8cb:	a8 02                	test   $0x2,%al
  jnz     seta20.1
    c8cd:	75 fa                	jne    c8c9 <seta20.1>

  movb    $0xd1,%al               # 0xd1 -> port 0x64
    c8cf:	b0 d1                	mov    $0xd1,%al
  outb    %al,$0x64
    c8d1:	e6 64                	out    %al,$0x64

0000c8d3 <seta20.2>:

seta20.2:
  inb     $0x64,%al               # Wait for not busy
    c8d3:	e4 64                	in     $0x64,%al
  testb   $02,%al
    c8d5:	a8 02                	test   $0x2,%al
  jnz     seta20.2
    c8d7:	75 fa                	jne    c8d3 <seta20.2>

  movb    $0xdf,%al               # 0xdf -> port 0x60
    c8d9:	b0 df                	mov    $0xdf,%al
  outb    %al,$0x60
    c8db:	e6 60                	out    %al,$0x60

  # Switch from real to protected mode, using a bootstrap GDT       this is vip ,but i don`t know it clearly now
  # and segment translation that makes virtual addresses 
  # identical to their physical addresses, so that the 
  # effective memory map does not change during the switch.
  lgdt    gdtdesc
    c8dd:	0f 01 16             	lgdtl  (%esi)
    c8e0:	64 c9                	fs leave 
  movl    %cr0, %eax
    c8e2:	0f 20 c0             	mov    %cr0,%eax
  orl     $CR0_PE_ON, %eax
    c8e5:	66 83 c8 01          	or     $0x1,%ax
  movl    %eax, %cr0
    c8e9:	0f 22 c0             	mov    %eax,%cr0
  
  # Jump to next instruction, but in 32-bit code segment.
  # Switches processor into 32-bit mode.
  ljmp    $PROT_MODE_CSEG, $protcseg
    c8ec:	ea                   	.byte 0xea
    c8ed:	31 c9                	xor    %ecx,%ecx
    c8ef:	08 00                	or     %al,(%eax)

0000c8f1 <msg>:
    c8f1:	0d 0a 0a 0d 6d       	or     $0x6d0d0a0a,%eax
    c8f6:	79 20                	jns    c918 <try+0xb>
    c8f8:	6b 65 72 6e          	imul   $0x6e,0x72(%ebp),%esp
    c8fc:	65 6c                	gs insb (%dx),%es:(%edi)
    c8fe:	20 69 73             	and    %ch,0x73(%ecx)
    c901:	20 72 75             	and    %dh,0x75(%edx)
    c904:	6e                   	outsb  %ds:(%esi),(%dx)
    c905:	69 6e 67 20 6a 6f 73 	imul   $0x736f6a20,0x67(%esi),%ebp
	...

0000c90d <try>:
    c90d:	0d 0a 0a 0d 74       	or     $0x740d0a0a,%eax
    c912:	72 79                	jb     c98d <io_out8+0x2>
    c914:	20 69 74             	and    %ch,0x74(%ecx)
    c917:	20 61 67             	and    %ah,0x67(%ecx)
    c91a:	61                   	popa   
    c91b:	69                   	.byte 0x69
    c91c:	6e                   	outsb  %ds:(%esi),(%dx)
	...

0000c91e <puts>:
  
try:
  .asciz "\r\n\n\rtry it again"

puts:
	movb (%si),%al
    c91e:	8a 04 83             	mov    (%ebx,%eax,4),%al
	add $1,%si
    c921:	c6 01 3c             	movb   $0x3c,(%ecx)
	cmp $0,%al
    c924:	00 74 09 b4          	add    %dh,-0x4c(%ecx,%ecx,1)
	je over
	movb $0x0e,%ah
    c928:	0e                   	push   %cs
	movw $15,%bx
    c929:	bb 0f 00 cd 10       	mov    $0x10cd000f,%ebx
	int $0x10
	jmp puts
    c92e:	eb ee                	jmp    c91e <puts>

0000c930 <over>:
over:
	ret	
    c930:	c3                   	ret    

0000c931 <protcseg>:
	
	
  .code32                     # Assemble for 32-bit mode
protcseg:
  # Set up the protected-mode data segment registers
  movw    $PROT_MODE_DSEG, %ax    # Our data segment selector
    c931:	66 b8 10 00          	mov    $0x10,%ax
  movw    %ax, %ds                # -> DS: Data Segment
    c935:	8e d8                	mov    %eax,%ds
  movw    %ax, %es                # -> ES: Extra Segment
    c937:	8e c0                	mov    %eax,%es
  movw    %ax, %fs                # -> FS
    c939:	8e e0                	mov    %eax,%fs
  movw    %ax, %gs                # -> GS
    c93b:	8e e8                	mov    %eax,%gs
  movw    %ax, %ss                # -> SS: Stack Segment
    c93d:	8e d0                	mov    %eax,%ss
  
  # Set up the stack pointer and call into C.
  movl    $start, %esp
    c93f:	bc 8c c8 00 00       	mov    $0xc88c,%esp
  call bootmain
    c944:	e8 80 fb ff ff       	call   c4c9 <bootmain>

0000c949 <spin>:

  # If bootmain returns (it shouldn't), loop.
spin:
  jmp spin
    c949:	eb fe                	jmp    c949 <spin>
    c94b:	90                   	nop

0000c94c <gdt>:
	...
    c954:	ff                   	(bad)  
    c955:	ff 00                	incl   (%eax)
    c957:	00 00                	add    %al,(%eax)
    c959:	9a cf 00 ff ff 00 00 	lcall  $0x0,$0xffff00cf
    c960:	00                   	.byte 0x0
    c961:	92                   	xchg   %eax,%edx
    c962:	cf                   	iret   
	...

0000c964 <gdtdesc>:
    c964:	17                   	pop    %ss
    c965:	00 4c c9 00          	add    %cl,0x0(%ecx,%ecx,8)
    c969:	00 66 90             	add    %ah,-0x70(%esi)
    c96c:	66 90                	xchg   %ax,%ax
    c96e:	66 90                	xchg   %ax,%ax

0000c970 <io_hlt>:

; 以下は実際の関数


io_hlt:	; void io_hlt(void);
	HLT
    c970:	f4                   	hlt    
	RET
    c971:	c3                   	ret    

0000c972 <io_cli>:
io_cli: 
	CLI
    c972:	fa                   	cli    
	RET
    c973:	c3                   	ret    

0000c974 <io_sti>:
io_sti:
	STI
    c974:	fb                   	sti    
	RET
    c975:	c3                   	ret    

0000c976 <io_read_eflags>:
io_read_eflags:
	PUSHFD		; PUSH EFLAGS  32 bit
    c976:	9c                   	pushf  
	POP 	EAX		; 32 bit
    c977:	58                   	pop    %eax
	RET
    c978:	c3                   	ret    

0000c979 <io_store_eflags>:
io_store_eflags:
	MOV		EAX, [ESP+4]
    c979:	8b 44 24 04          	mov    0x4(%esp),%eax
	PUSH	EAX
    c97d:	50                   	push   %eax
	POPFD
    c97e:	9d                   	popf   
	RET
    c97f:	c3                   	ret    

0000c980 <write_mem8>:
	
write_mem8:
	MOV		ECX, [ESP+4]
    c980:	8b 4c 24 04          	mov    0x4(%esp),%ecx
	MOV		AL,	 [ESP+8]
    c984:	8a 44 24 08          	mov    0x8(%esp),%al
	MOV		[ECX], AL
    c988:	88 01                	mov    %al,(%ecx)
	RET
    c98a:	c3                   	ret    

0000c98b <io_out8>:
io_out8:
	MOV		EDX, [ESP+4]	;port
    c98b:	8b 54 24 04          	mov    0x4(%esp),%edx
	MOV		AL,	[ESP+8]		;data
    c98f:	8a 44 24 08          	mov    0x8(%esp),%al
	OUT 	DX, AL
    c993:	ee                   	out    %al,(%dx)
	RET
    c994:	c3                   	ret    

Disassembly of section .data:

0000cae0 <hankaku>:
	...
    caf0:	00 00 38 44 82 aa aa 82 82 aa 92 44 38 00 00 00     ..8D.......D8...
    cb00:	00 00 38 7c fe d6 d6 fe fe d6 ee 7c 38 00 00 00     ..8|.......|8...
    cb10:	00 00 00 00 6c fe fe fe 7c 38 10 00 00 00 00 00     ....l...|8......
    cb20:	00 00 00 00 10 38 7c fe 7c 38 10 00 00 00 00 00     .....8|.|8......
    cb30:	00 00 00 00 10 38 54 fe 54 10 38 00 00 00 00 00     .....8T.T.8.....
    cb40:	00 00 00 00 10 38 7c fe d6 10 38 00 00 00 00 00     .....8|...8.....
    cb50:	00 00 00 00 00 00 18 3c 3c 18 00 00 00 00 00 00     .......<<.......
    cb60:	ff ff ff ff ff ff e7 c3 c3 e7 ff ff ff ff ff ff     ................
    cb70:	00 00 00 00 00 3c 66 42 42 66 3c 00 00 00 00 00     .....<fBBf<.....
    cb80:	ff ff ff ff ff c3 99 bd bd 99 c3 ff ff ff ff ff     ................
    cb90:	00 10 38 54 92 10 10 38 44 82 82 82 44 38 00 00     ..8T...8D...D8..
    cba0:	00 38 44 82 82 82 44 38 10 10 fe 10 10 10 00 00     .8D...D8........
    cbb0:	00 00 0c 0e 0b 0b 0a 08 08 18 78 f8 70 00 00 00     ..........x.p...
    cbc0:	00 00 1f 1f 11 11 11 11 11 11 77 ff 66 00 00 00     ..........w.f...
    cbd0:	00 00 00 00 10 54 38 28 38 54 10 00 00 00 00 00     .....T8(8T......
    cbe0:	00 80 c0 e0 f0 f8 fc fe fc f8 f0 e0 c0 80 00 00     ................
    cbf0:	00 02 06 0e 1e 3e 7e fe 7e 3e 1e 0e 06 02 00 00     .....>~.~>......
    cc00:	00 00 10 38 54 92 10 10 10 92 54 38 10 00 00 00     ...8T.....T8....
    cc10:	00 00 44 44 44 44 44 44 44 44 00 00 44 44 00 00     ..DDDDDDDD..DD..
    cc20:	00 3e 4a 8a 8a 8a 8a 4a 3a 0a 0a 0a 0a 0a 00 00     .>J....J:.......
    cc30:	7c 82 40 20 38 44 82 82 82 44 38 08 04 82 7c 00     |.@ 8D...D8...|.
	...
    cc48:	00 00 00 fe fe fe 00 00 00 00 10 38 54 92 10 10     ...........8T...
    cc58:	10 92 54 38 10 7c 00 00 00 10 38 54 92 10 10 10     ..T8.|....8T....
    cc68:	10 10 10 10 10 10 00 00 00 10 10 10 10 10 10 10     ................
    cc78:	10 10 92 54 38 10 00 00 00 00 00 00 10 08 04 fe     ...T8...........
    cc88:	04 08 10 00 00 00 00 00 00 00 00 00 10 20 40 fe     ............. @.
    cc98:	40 20 10 00 00 00 00 00 00 00 00 00 00 00 00 00     @ ..............
    cca8:	00 00 00 80 80 fe 00 00 00 00 00 00 00 28 44 fe     .............(D.
    ccb8:	44 28 00 00 00 00 00 00 00 00 00 00 10 10 38 38     D(............88
    ccc8:	7c 7c fe fe 00 00 00 00 00 00 00 00 fe fe 7c 7c     ||............||
    ccd8:	38 38 10 10 00 00 00 00 00 00 00 00 00 00 00 00     88..............
	...
    ccf0:	00 10 10 10 10 10 10 10 10 10 00 00 10 10 00 00     ................
    cd00:	28 28 28 00 00 00 00 00 00 00 00 00 00 00 00 00     (((.............
    cd10:	00 44 44 44 fe 44 44 44 44 44 fe 44 44 44 00 00     .DDD.DDDDD.DDD..
    cd20:	10 3a 56 92 92 90 50 38 14 12 92 92 d4 b8 10 10     .:V...P8........
    cd30:	62 92 94 94 68 08 10 10 20 2c 52 52 92 8c 00 00     b...h... ,RR....
    cd40:	00 70 88 88 88 90 60 47 a2 92 8a 84 46 39 00 00     .p....`G....F9..
    cd50:	04 08 10 00 00 00 00 00 00 00 00 00 00 00 00 00     ................
    cd60:	02 04 08 08 10 10 10 10 10 10 10 08 08 04 02 00     ................
    cd70:	80 40 20 20 10 10 10 10 10 10 10 20 20 40 80 00     .@  .......  @..
    cd80:	00 00 00 00 00 10 92 54 38 54 92 10 00 00 00 00     .......T8T......
    cd90:	00 00 00 00 00 10 10 10 fe 10 10 10 00 00 00 00     ................
	...
    cda8:	00 00 00 18 18 08 08 10 00 00 00 00 00 00 00 00     ................
    cdb8:	fe 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00     ................
    cdc8:	00 00 00 00 18 18 00 00 02 02 04 04 08 08 08 10     ................
    cdd8:	10 20 20 40 40 40 80 80 00 18 24 24 42 42 42 42     .  @@@....$$BBBB
    cde8:	42 42 42 24 24 18 00 00 00 08 18 28 08 08 08 08     BBB$$......(....
    cdf8:	08 08 08 08 08 3e 00 00 00 18 24 42 42 02 04 08     .....>....$BB...
    ce08:	10 20 20 40 40 7e 00 00 00 18 24 42 02 02 04 18     .  @@~....$B....
    ce18:	04 02 02 42 24 18 00 00 00 0c 0c 0c 14 14 14 24     ...B$..........$
    ce28:	24 44 7e 04 04 1e 00 00 00 7c 40 40 40 58 64 02     $D~......|@@@Xd.
    ce38:	02 02 02 42 24 18 00 00 00 18 24 42 40 58 64 42     ...B$.....$B@XdB
    ce48:	42 42 42 42 24 18 00 00 00 7e 42 42 04 04 08 08     BBBB$....~BB....
    ce58:	08 10 10 10 10 38 00 00 00 18 24 42 42 42 24 18     .....8....$BBB$.
    ce68:	24 42 42 42 24 18 00 00 00 18 24 42 42 42 42 42     $BBB$.....$BBBBB
    ce78:	26 1a 02 42 24 18 00 00 00 00 00 00 00 18 18 00     &..B$...........
    ce88:	00 00 00 00 18 18 00 00 00 00 00 00 00 18 18 00     ................
    ce98:	00 00 00 18 18 08 08 10 00 02 04 08 10 20 40 80     ............. @.
    cea8:	80 40 20 10 08 04 02 00 00 00 00 00 00 00 fe 00     .@ .............
    ceb8:	00 fe 00 00 00 00 00 00 00 80 40 20 10 08 04 02     ..........@ ....
    cec8:	02 04 08 10 20 40 80 00 00 38 44 82 82 82 04 08     .... @...8D.....
    ced8:	10 10 00 00 18 18 00 00 00 38 44 82 9a aa aa aa     .........8D.....
    cee8:	aa aa 9c 80 46 38 00 00 00 18 18 18 18 24 24 24     ....F8.......$$$
    cef8:	24 7e 42 42 42 e7 00 00 00 f0 48 44 44 44 48 78     $~BBB.....HDDDHx
    cf08:	44 42 42 42 44 f8 00 00 00 3a 46 42 82 80 80 80     DBBBD....:FB....
    cf18:	80 80 82 42 44 38 00 00 00 f8 44 44 42 42 42 42     ...BD8....DDBBBB
    cf28:	42 42 42 44 44 f8 00 00 00 fe 42 42 40 40 44 7c     BBBDD.....BB@@D|
    cf38:	44 40 40 42 42 fe 00 00 00 fe 42 42 40 40 44 7c     D@@BB.....BB@@D|
    cf48:	44 44 40 40 40 f0 00 00 00 3a 46 42 82 80 80 9e     DD@@@....:FB....
    cf58:	82 82 82 42 46 38 00 00 00 e7 42 42 42 42 42 7e     ...BF8....BBBBB~
    cf68:	42 42 42 42 42 e7 00 00 00 7c 10 10 10 10 10 10     BBBBB....|......
    cf78:	10 10 10 10 10 7c 00 00 00 1f 04 04 04 04 04 04     .....|..........
    cf88:	04 04 04 04 84 48 30 00 00 e7 42 44 48 50 50 60     .....H0...BDHPP`
    cf98:	50 50 48 44 42 e7 00 00 00 f0 40 40 40 40 40 40     PPHDB.....@@@@@@
    cfa8:	40 40 40 42 42 fe 00 00 00 c3 42 66 66 66 5a 5a     @@@BB.....BfffZZ
    cfb8:	5a 42 42 42 42 e7 00 00 00 c7 42 62 62 52 52 52     ZBBBB.....BbbRRR
    cfc8:	4a 4a 4a 46 46 e2 00 00 00 38 44 82 82 82 82 82     JJJFF....8D.....
    cfd8:	82 82 82 82 44 38 00 00 00 f8 44 42 42 42 44 78     ....D8....DBBBDx
    cfe8:	40 40 40 40 40 f0 00 00 00 38 44 82 82 82 82 82     @@@@@....8D.....
    cff8:	82 82 92 8a 44 3a 00 00 00 fc 42 42 42 42 7c 44     ....D:....BBBB|D
    d008:	42 42 42 42 42 e7 00 00 00 3a 46 82 82 80 40 38     BBBBB....:F...@8
    d018:	04 02 82 82 c4 b8 00 00 00 fe 92 92 10 10 10 10     ................
    d028:	10 10 10 10 10 7c 00 00 00 e7 42 42 42 42 42 42     .....|....BBBBBB
    d038:	42 42 42 42 24 3c 00 00 00 e7 42 42 42 42 24 24     BBBB$<....BBBB$$
    d048:	24 24 18 18 18 18 00 00 00 e7 42 42 42 5a 5a 5a     $$........BBBZZZ
    d058:	5a 24 24 24 24 24 00 00 00 e7 42 42 24 24 24 18     Z$$$$$....BB$$$.
    d068:	24 24 24 42 42 e7 00 00 00 ee 44 44 44 28 28 28     $$$BB.....DDD(((
    d078:	10 10 10 10 10 7c 00 00 00 fe 84 84 08 08 10 10     .....|..........
    d088:	20 20 40 42 82 fe 00 00 00 3e 20 20 20 20 20 20       @B.....>      
    d098:	20 20 20 20 20 20 3e 00 80 80 40 40 20 20 20 10           >...@@   .
    d0a8:	10 08 08 04 04 04 02 02 00 7c 04 04 04 04 04 04     .........|......
    d0b8:	04 04 04 04 04 04 7c 00 00 10 28 44 82 00 00 00     ......|...(D....
	...
    d0dc:	00 00 fe 00 10 08 04 00 00 00 00 00 00 00 00 00     ................
	...
    d0f4:	00 70 08 04 3c 44 84 84 8c 76 00 00 c0 40 40 40     .p..<D...v...@@@
    d104:	40 58 64 42 42 42 42 42 64 58 00 00 00 00 00 00     @XdBBBBBdX......
    d114:	00 30 4c 84 84 80 80 82 44 38 00 00 0c 04 04 04     .0L.....D8......
    d124:	04 34 4c 84 84 84 84 84 4c 36 00 00 00 00 00 00     .4L.....L6......
    d134:	00 38 44 82 82 fc 80 82 42 3c 00 00 0e 10 10 10     .8D.....B<......
    d144:	10 7c 10 10 10 10 10 10 10 7c 00 00 00 00 00 00     .|.......|......
    d154:	00 36 4c 84 84 84 84 4c 34 04 04 78 c0 40 40 40     .6L....L4..x.@@@
    d164:	40 58 64 42 42 42 42 42 42 e3 00 00 00 10 10 00     @XdBBBBBB.......
    d174:	00 30 10 10 10 10 10 10 10 38 00 00 00 04 04 00     .0.......8......
    d184:	00 0c 04 04 04 04 04 04 04 08 08 30 c0 40 40 40     ...........0.@@@
    d194:	40 4e 44 48 50 60 50 48 44 e6 00 00 30 10 10 10     @NDHP`PHD...0...
    d1a4:	10 10 10 10 10 10 10 10 10 38 00 00 00 00 00 00     .........8......
    d1b4:	00 f6 49 49 49 49 49 49 49 db 00 00 00 00 00 00     ..IIIIIII.......
    d1c4:	00 d8 64 42 42 42 42 42 42 e3 00 00 00 00 00 00     ..dBBBBBB.......
    d1d4:	00 38 44 82 82 82 82 82 44 38 00 00 00 00 00 00     .8D.....D8......
    d1e4:	00 d8 64 42 42 42 42 42 64 58 40 e0 00 00 00 00     ..dBBBBBdX@.....
    d1f4:	00 34 4c 84 84 84 84 84 4c 34 04 0e 00 00 00 00     .4L.....L4......
    d204:	00 dc 62 42 40 40 40 40 40 e0 00 00 00 00 00 00     ..bB@@@@@.......
    d214:	00 7a 86 82 c0 38 06 82 c2 bc 00 00 00 00 10 10     .z...8..........
    d224:	10 7c 10 10 10 10 10 10 10 0e 00 00 00 00 00 00     .|..............
    d234:	00 c6 42 42 42 42 42 42 46 3b 00 00 00 00 00 00     ..BBBBBBF;......
    d244:	00 e7 42 42 42 24 24 24 18 18 00 00 00 00 00 00     ..BBB$$$........
    d254:	00 e7 42 42 5a 5a 5a 24 24 24 00 00 00 00 00 00     ..BBZZZ$$$......
    d264:	00 c6 44 28 28 10 28 28 44 c6 00 00 00 00 00 00     ..D((.((D.......
    d274:	00 e7 42 42 24 24 24 18 18 10 10 60 00 00 00 00     ..BB$$$....`....
    d284:	00 fe 82 84 08 10 20 42 82 fe 00 00 00 06 08 10     ...... B........
    d294:	10 10 10 60 10 10 10 10 08 06 00 00 10 10 10 10     ...`............
    d2a4:	10 10 10 10 10 10 10 10 10 10 10 10 00 60 10 08     .............`..
    d2b4:	08 08 08 06 08 08 08 08 10 60 00 00 00 72 8c 00     .........`...r..
	...
    d2d4:	10 28 44 82 fe 82 fe 00 00 00 00 00 00 38 44 82     .(D..........8D.
    d2e4:	80 80 80 80 80 80 80 82 44 38 10 20 00 00 24 24     ........D8. ..$$
    d2f4:	00 82 82 82 82 82 82 82 42 3e 00 00 0c 08 10 00     ........B>......
    d304:	00 38 44 82 82 fe 80 82 44 38 00 00 00 10 28 44     .8D.....D8....(D
    d314:	00 78 04 04 3c 44 84 84 44 3e 00 00 00 00 24 24     .x..<D..D>....$$
    d324:	00 78 04 04 3c 44 84 84 44 3e 00 00 10 08 04 00     .x..<D..D>......
    d334:	00 78 04 04 3c 44 84 84 44 3e 00 00 00 18 24 18     .x..<D..D>....$.
    d344:	00 78 04 04 3c 44 84 84 44 3e 00 00 00 00 00 00     .x..<D..D>......
    d354:	00 3c 42 80 80 80 80 80 42 3c 08 10 00 10 28 44     .<B.....B<....(D
    d364:	00 38 44 82 82 fe 80 82 44 38 00 00 00 00 24 24     .8D.....D8....$$
    d374:	00 38 44 82 82 fe 80 82 44 38 00 00 10 08 04 00     .8D.....D8......
    d384:	00 38 44 82 82 fe 80 82 44 38 00 00 00 00 24 24     .8D.....D8....$$
    d394:	00 10 10 10 10 10 10 10 10 10 00 00 00 10 28 44     ..............(D
    d3a4:	00 10 10 10 10 10 10 10 10 10 00 00 10 08 04 00     ................
    d3b4:	00 10 10 10 10 10 10 10 10 10 00 00 24 24 00 38     ............$$.8
    d3c4:	44 82 82 82 82 fe 82 82 82 82 00 00 00 38 44 38     D............8D8
    d3d4:	44 82 82 82 82 fe 82 82 82 82 00 00 0c 08 10 fe     D...............
    d3e4:	80 80 80 80 f8 80 80 80 80 fe 00 00 00 00 00 00     ................
    d3f4:	00 60 1c 12 72 9e 90 90 92 6c 00 00 0c 10 20 28     .`..r....l.... (
    d404:	28 28 fe 28 28 28 28 28 28 28 00 00 00 10 28 44     ((.(((((((....(D
    d414:	00 38 44 82 82 82 82 82 44 38 00 00 00 00 24 24     .8D.....D8....$$
    d424:	00 38 44 82 82 82 82 82 44 38 00 00 10 08 04 00     .8D.....D8......
    d434:	00 38 44 82 82 82 82 82 44 38 00 00 00 10 28 44     .8D.....D8....(D
    d444:	00 82 82 82 82 82 82 82 42 3e 00 00 10 08 04 00     ........B>......
    d454:	00 82 82 82 82 82 82 82 42 3e 00 00 00 00 24 24     ........B>....$$
    d464:	00 82 82 44 44 28 28 10 10 20 20 40 24 24 00 38     ...DD((..  @$$.8
    d474:	44 82 82 82 82 82 82 82 44 38 00 00 24 24 00 82     D.......D8..$$..
    d484:	82 82 82 82 82 82 82 82 44 38 00 00 00 28 28 28     ........D8...(((
    d494:	3c 6a a8 a8 a8 a8 a8 6a 3c 28 28 28 00 0c 12 20     <j.....j<(((... 
    d4a4:	20 20 fc 20 20 20 60 a0 b2 4c 00 00 00 82 82 44       .   `..L.....D
    d4b4:	28 10 fe 10 10 fe 10 10 10 10 00 00 00 e0 90 88     (...............
    d4c4:	88 88 94 e4 9f 84 84 84 84 84 00 00 00 0c 12 10     ................
    d4d4:	10 10 fe 10 10 10 10 10 90 60 00 00 0c 08 10 00     .........`......
    d4e4:	00 78 04 04 3c 44 84 84 44 3e 00 00 0c 08 10 00     .x..<D..D>......
    d4f4:	00 10 10 10 10 10 10 10 10 10 00 00 0c 08 10 00     ................
    d504:	00 38 44 82 82 82 82 82 44 38 00 00 0c 08 10 00     .8D.....D8......
    d514:	00 82 82 82 82 82 82 82 42 3e 00 00 00 12 2a 24     ........B>....*$
    d524:	00 f8 84 82 82 82 82 82 82 82 00 00 12 2a 24 00     .............*$.
    d534:	82 c2 c2 a2 92 92 8a 86 86 82 00 00 00 00 00 78     ...............x
    d544:	04 04 3c 44 84 84 44 3e 00 fe 00 00 00 00 00 38     ..<D..D>.......8
    d554:	44 82 82 82 82 82 44 38 00 fe 00 00 00 10 10 00     D.....D8........
    d564:	00 10 10 20 44 82 82 82 44 38 00 00 00 00 00 00     ... D...D8......
    d574:	00 00 00 00 00 00 fe 80 80 80 00 00 00 00 00 00     ................
    d584:	00 00 00 00 00 00 fe 02 02 02 00 00 00 10 30 10     ..............0.
    d594:	10 10 00 fe 00 78 04 38 40 7c 00 00 00 10 30 10     .....x.8@|....0.
    d5a4:	10 10 00 fe 00 18 28 48 7c 08 00 00 00 10 10 00     ......(H|.......
    d5b4:	00 10 10 10 10 10 10 10 10 10 00 00 00 00 00 00     ................
    d5c4:	12 24 48 90 90 48 24 12 00 00 00 00 00 00 00 00     .$H..H$.........
    d5d4:	90 48 24 12 12 24 48 90 00 00 00 00 11 44 11 44     .H$..$H......D.D
    d5e4:	11 44 11 44 11 44 11 44 11 44 11 44 55 aa 55 aa     .D.D.D.D.D.DU.U.
    d5f4:	55 aa 55 aa 55 aa 55 aa 55 aa 55 aa 77 dd 77 dd     U.U.U.U.U.U.w.w.
    d604:	77 dd 77 dd 77 dd 77 dd 77 dd 77 dd 10 10 10 10     w.w.w.w.w.w.....
    d614:	10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10     ................
    d624:	10 10 10 f0 10 10 10 10 10 10 10 10 10 10 10 10     ................
    d634:	10 10 10 f0 10 f0 10 10 10 10 10 10 14 14 14 14     ................
    d644:	14 14 14 f4 14 14 14 14 14 14 14 14 00 00 00 00     ................
    d654:	00 00 00 fc 14 14 14 14 14 14 14 14 00 00 00 00     ................
    d664:	00 00 00 f0 10 f0 10 10 10 10 10 10 14 14 14 14     ................
    d674:	14 14 14 f4 04 f4 14 14 14 14 14 14 14 14 14 14     ................
    d684:	14 14 14 14 14 14 14 14 14 14 14 14 00 00 00 00     ................
    d694:	00 00 00 fc 04 f4 14 14 14 14 14 14 14 14 14 14     ................
    d6a4:	14 14 14 f4 04 fc 00 00 00 00 00 00 14 14 14 14     ................
    d6b4:	14 14 14 fc 00 00 00 00 00 00 00 00 10 10 10 10     ................
    d6c4:	10 10 10 f0 10 f0 00 00 00 00 00 00 00 00 00 00     ................
    d6d4:	00 00 00 f0 10 10 10 10 10 10 10 10 10 10 10 10     ................
    d6e4:	10 10 10 1f 00 00 00 00 00 00 00 00 10 10 10 10     ................
    d6f4:	10 10 10 ff 00 00 00 00 00 00 00 00 00 00 00 00     ................
    d704:	00 00 00 ff 10 10 10 10 10 10 10 10 10 10 10 10     ................
    d714:	10 10 10 1f 10 10 10 10 10 10 10 10 00 00 00 00     ................
    d724:	00 00 00 ff 00 00 00 00 00 00 00 00 10 10 10 10     ................
    d734:	10 10 10 ff 10 10 10 10 10 10 10 10 10 10 10 10     ................
    d744:	10 10 10 1f 10 1f 10 10 10 10 10 10 14 14 14 14     ................
    d754:	14 14 14 17 14 14 14 14 14 14 14 14 14 14 14 14     ................
    d764:	14 14 14 17 10 1f 00 00 00 00 00 00 00 00 00 00     ................
    d774:	00 00 00 1f 10 17 14 14 14 14 14 14 14 14 14 14     ................
    d784:	14 14 14 f7 00 ff 00 00 00 00 00 00 00 00 00 00     ................
    d794:	00 00 00 ff 00 f7 14 14 14 14 14 14 14 14 14 14     ................
    d7a4:	14 14 14 17 10 17 14 14 14 14 14 14 00 00 00 00     ................
    d7b4:	00 00 00 ff 00 ff 00 00 00 00 00 00 14 14 14 14     ................
    d7c4:	14 14 14 f7 00 f7 14 14 14 14 14 14 10 10 10 10     ................
    d7d4:	10 10 10 ff 00 ff 00 00 00 00 00 00 14 14 14 14     ................
    d7e4:	14 14 14 ff 00 00 00 00 00 00 00 00 00 00 00 00     ................
    d7f4:	00 00 00 ff 00 ff 10 10 10 10 10 10 00 00 00 00     ................
    d804:	00 00 00 ff 14 14 14 14 14 14 14 14 14 14 14 14     ................
    d814:	14 14 14 1f 00 00 00 00 00 00 00 00 10 10 10 10     ................
    d824:	10 10 10 1f 10 1f 00 00 00 00 00 00 00 00 00 00     ................
    d834:	00 00 00 1f 10 1f 10 10 10 10 10 10 00 00 00 00     ................
    d844:	00 00 00 1f 14 14 14 14 14 14 14 14 14 14 14 14     ................
    d854:	14 14 14 f7 14 14 14 14 14 14 14 14 10 10 10 10     ................
    d864:	10 10 10 ff 10 ff 10 10 10 10 10 10 10 10 10 10     ................
    d874:	10 10 10 f0 00 00 00 00 00 00 00 00 00 00 00 00     ................
    d884:	00 00 00 1f 10 10 10 10 10 10 10 10 ff ff ff ff     ................
    d894:	ff ff ff ff ff ff ff ff ff ff ff ff 00 00 00 00     ................
    d8a4:	00 00 00 00 ff ff ff ff ff ff ff ff f0 f0 f0 f0     ................
    d8b4:	f0 f0 f0 f0 f0 f0 f0 f0 f0 f0 f0 f0 0f 0f 0f 0f     ................
    d8c4:	0f 0f 0f 0f 0f 0f 0f 0f 0f 0f 0f 0f ff ff ff ff     ................
    d8d4:	ff ff ff ff 00 00 00 00 00 00 00 00 00 00 00 00     ................
	...

0000dae0 <DISPLAY_X_SIZE>:
    dae0:	40 01 00 00                                         @...

0000dae4 <DISPLAY_Y_SIZE>:
    dae4:	c8 00 00 00                                         ....

0000dae8 <DISPLAY_ADDRE>:
    dae8:	00 00 0a 00 00 00 00 00 00 00 00 00 00 00 00 00     ................
	...

0000db00 <rgb_table.1015>:
    db00:	00 00 00 ff 00 00 00 ff 00 ff ff 00 00 00 ff ff     ................
    db10:	00 ff 00 ff ff ff ff ff c6 c6 c6 84 00 00 00 84     ................
    db20:	00 84 84 00 00 00 84 84 00 84 00 84 84 84 84 84     ................

0000db30 <msg.1062>:
    db30:	49 27 6d 20 53 75 43 69 63 61 64 61 2e 00 00 00     I'm SuCicada....

0000db40 <font_A.1061>:
    db40:	00 18 18 18 18 24 24 24 24 7e 42 42 42 e7 00 00     .....$$$$~BBB...
