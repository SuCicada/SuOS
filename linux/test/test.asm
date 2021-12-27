
a.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	callq  *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	retq   

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 8a 2f 00 00    	pushq  0x2f8a(%rip)        # 3fb0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 8b 2f 00 00 	bnd jmpq *0x2f8b(%rip)        # 3fb8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	pushq  $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmpq 1020 <.plt>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	pushq  $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmpq 1020 <.plt>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	pushq  $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmpq 1020 <.plt>
    105f:	90                   	nop

Disassembly of section .plt.got:

0000000000001060 <__cxa_finalize@plt>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	f2 ff 25 8d 2f 00 00 	bnd jmpq *0x2f8d(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    106b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001070 <puts@plt>:
    1070:	f3 0f 1e fa          	endbr64 
    1074:	f2 ff 25 45 2f 00 00 	bnd jmpq *0x2f45(%rip)        # 3fc0 <puts@GLIBC_2.2.5>
    107b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001080 <__stack_chk_fail@plt>:
    1080:	f3 0f 1e fa          	endbr64 
    1084:	f2 ff 25 3d 2f 00 00 	bnd jmpq *0x2f3d(%rip)        # 3fc8 <__stack_chk_fail@GLIBC_2.4>
    108b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001090 <printf@plt>:
    1090:	f3 0f 1e fa          	endbr64 
    1094:	f2 ff 25 35 2f 00 00 	bnd jmpq *0x2f35(%rip)        # 3fd0 <printf@GLIBC_2.2.5>
    109b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000010a0 <_start>:
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	31 ed                	xor    %ebp,%ebp
    10a6:	49 89 d1             	mov    %rdx,%r9
    10a9:	5e                   	pop    %rsi
    10aa:	48 89 e2             	mov    %rsp,%rdx
    10ad:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    10b1:	50                   	push   %rax
    10b2:	54                   	push   %rsp
    10b3:	4c 8d 05 f6 03 00 00 	lea    0x3f6(%rip),%r8        # 14b0 <__libc_csu_fini>
    10ba:	48 8d 0d 7f 03 00 00 	lea    0x37f(%rip),%rcx        # 1440 <__libc_csu_init>
    10c1:	48 8d 3d 00 03 00 00 	lea    0x300(%rip),%rdi        # 13c8 <main>
    10c8:	ff 15 12 2f 00 00    	callq  *0x2f12(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    10ce:	f4                   	hlt    
    10cf:	90                   	nop

00000000000010d0 <deregister_tm_clones>:
    10d0:	48 8d 3d 39 2f 00 00 	lea    0x2f39(%rip),%rdi        # 4010 <__TMC_END__>
    10d7:	48 8d 05 32 2f 00 00 	lea    0x2f32(%rip),%rax        # 4010 <__TMC_END__>
    10de:	48 39 f8             	cmp    %rdi,%rax
    10e1:	74 15                	je     10f8 <deregister_tm_clones+0x28>
    10e3:	48 8b 05 ee 2e 00 00 	mov    0x2eee(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    10ea:	48 85 c0             	test   %rax,%rax
    10ed:	74 09                	je     10f8 <deregister_tm_clones+0x28>
    10ef:	ff e0                	jmpq   *%rax
    10f1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10f8:	c3                   	retq   
    10f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001100 <register_tm_clones>:
    1100:	48 8d 3d 09 2f 00 00 	lea    0x2f09(%rip),%rdi        # 4010 <__TMC_END__>
    1107:	48 8d 35 02 2f 00 00 	lea    0x2f02(%rip),%rsi        # 4010 <__TMC_END__>
    110e:	48 29 fe             	sub    %rdi,%rsi
    1111:	48 89 f0             	mov    %rsi,%rax
    1114:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1118:	48 c1 f8 03          	sar    $0x3,%rax
    111c:	48 01 c6             	add    %rax,%rsi
    111f:	48 d1 fe             	sar    %rsi
    1122:	74 14                	je     1138 <register_tm_clones+0x38>
    1124:	48 8b 05 c5 2e 00 00 	mov    0x2ec5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    112b:	48 85 c0             	test   %rax,%rax
    112e:	74 08                	je     1138 <register_tm_clones+0x38>
    1130:	ff e0                	jmpq   *%rax
    1132:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1138:	c3                   	retq   
    1139:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001140 <__do_global_dtors_aux>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	80 3d c5 2e 00 00 00 	cmpb   $0x0,0x2ec5(%rip)        # 4010 <__TMC_END__>
    114b:	75 2b                	jne    1178 <__do_global_dtors_aux+0x38>
    114d:	55                   	push   %rbp
    114e:	48 83 3d a2 2e 00 00 	cmpq   $0x0,0x2ea2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1155:	00 
    1156:	48 89 e5             	mov    %rsp,%rbp
    1159:	74 0c                	je     1167 <__do_global_dtors_aux+0x27>
    115b:	48 8b 3d a6 2e 00 00 	mov    0x2ea6(%rip),%rdi        # 4008 <__dso_handle>
    1162:	e8 f9 fe ff ff       	callq  1060 <__cxa_finalize@plt>
    1167:	e8 64 ff ff ff       	callq  10d0 <deregister_tm_clones>
    116c:	c6 05 9d 2e 00 00 01 	movb   $0x1,0x2e9d(%rip)        # 4010 <__TMC_END__>
    1173:	5d                   	pop    %rbp
    1174:	c3                   	retq   
    1175:	0f 1f 00             	nopl   (%rax)
    1178:	c3                   	retq   
    1179:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001180 <frame_dummy>:
    1180:	f3 0f 1e fa          	endbr64 
    1184:	e9 77 ff ff ff       	jmpq   1100 <register_tm_clones>

0000000000001189 <su_sprintf>:
    1189:	f3 0f 1e fa          	endbr64 
    118d:	55                   	push   %rbp
    118e:	48 89 e5             	mov    %rsp,%rbp
    1191:	48 81 ec e0 00 00 00 	sub    $0xe0,%rsp
    1198:	48 89 bd 28 ff ff ff 	mov    %rdi,-0xd8(%rbp)
    119f:	48 89 b5 20 ff ff ff 	mov    %rsi,-0xe0(%rbp)
    11a6:	48 89 95 60 ff ff ff 	mov    %rdx,-0xa0(%rbp)
    11ad:	48 89 8d 68 ff ff ff 	mov    %rcx,-0x98(%rbp)
    11b4:	4c 89 85 70 ff ff ff 	mov    %r8,-0x90(%rbp)
    11bb:	4c 89 8d 78 ff ff ff 	mov    %r9,-0x88(%rbp)
    11c2:	84 c0                	test   %al,%al
    11c4:	74 20                	je     11e6 <su_sprintf+0x5d>
    11c6:	0f 29 45 80          	movaps %xmm0,-0x80(%rbp)
    11ca:	0f 29 4d 90          	movaps %xmm1,-0x70(%rbp)
    11ce:	0f 29 55 a0          	movaps %xmm2,-0x60(%rbp)
    11d2:	0f 29 5d b0          	movaps %xmm3,-0x50(%rbp)
    11d6:	0f 29 65 c0          	movaps %xmm4,-0x40(%rbp)
    11da:	0f 29 6d d0          	movaps %xmm5,-0x30(%rbp)
    11de:	0f 29 75 e0          	movaps %xmm6,-0x20(%rbp)
    11e2:	0f 29 7d f0          	movaps %xmm7,-0x10(%rbp)
    11e6:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
    11ed:	48 89 85 40 ff ff ff 	mov    %rax,-0xc0(%rbp)
    11f4:	48 8d 85 20 ff ff ff 	lea    -0xe0(%rbp),%rax
    11fb:	48 83 c0 40          	add    $0x40,%rax
    11ff:	48 89 85 48 ff ff ff 	mov    %rax,-0xb8(%rbp)
    1206:	e9 a0 00 00 00       	jmpq   12ab <su_sprintf+0x122>
    120b:	80 bd 37 ff ff ff 25 	cmpb   $0x25,-0xc9(%rbp)
    1212:	74 7b                	je     128f <su_sprintf+0x106>
    1214:	48 8b 85 20 ff ff ff 	mov    -0xe0(%rbp),%rax
    121b:	48 83 e8 01          	sub    $0x1,%rax
    121f:	0f b6 00             	movzbl (%rax),%eax
    1222:	3c 25                	cmp    $0x25,%al
    1224:	75 51                	jne    1277 <su_sprintf+0xee>
    1226:	0f be 85 37 ff ff ff 	movsbl -0xc9(%rbp),%eax
    122d:	83 f8 64             	cmp    $0x64,%eax
    1230:	75 5d                	jne    128f <su_sprintf+0x106>
    1232:	48 8b 85 48 ff ff ff 	mov    -0xb8(%rbp),%rax
    1239:	8b 00                	mov    (%rax),%eax
    123b:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    1241:	48 83 85 48 ff ff ff 	addq   $0x4,-0xb8(%rbp)
    1248:	04 
    1249:	48 8b 95 40 ff ff ff 	mov    -0xc0(%rbp),%rdx
    1250:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    1256:	48 89 d6             	mov    %rdx,%rsi
    1259:	89 c7                	mov    %eax,%edi
    125b:	e8 74 00 00 00       	callq  12d4 <int2str>
    1260:	89 85 3c ff ff ff    	mov    %eax,-0xc4(%rbp)
    1266:	8b 85 3c ff ff ff    	mov    -0xc4(%rbp),%eax
    126c:	48 98                	cltq   
    126e:	48 01 85 40 ff ff ff 	add    %rax,-0xc0(%rbp)
    1275:	eb 18                	jmp    128f <su_sprintf+0x106>
    1277:	48 8b 85 40 ff ff ff 	mov    -0xc0(%rbp),%rax
    127e:	0f b6 95 37 ff ff ff 	movzbl -0xc9(%rbp),%edx
    1285:	88 10                	mov    %dl,(%rax)
    1287:	48 83 85 40 ff ff ff 	addq   $0x1,-0xc0(%rbp)
    128e:	01 
    128f:	48 8b 85 40 ff ff ff 	mov    -0xc0(%rbp),%rax
    1296:	c6 00 00             	movb   $0x0,(%rax)
    1299:	48 8b 85 20 ff ff ff 	mov    -0xe0(%rbp),%rax
    12a0:	48 83 c0 01          	add    $0x1,%rax
    12a4:	48 89 85 20 ff ff ff 	mov    %rax,-0xe0(%rbp)
    12ab:	48 8b 85 20 ff ff ff 	mov    -0xe0(%rbp),%rax
    12b2:	0f b6 00             	movzbl (%rax),%eax
    12b5:	88 85 37 ff ff ff    	mov    %al,-0xc9(%rbp)
    12bb:	80 bd 37 ff ff ff 00 	cmpb   $0x0,-0xc9(%rbp)
    12c2:	74 0d                	je     12d1 <su_sprintf+0x148>
    12c4:	80 bd 37 ff ff ff 00 	cmpb   $0x0,-0xc9(%rbp)
    12cb:	0f 85 3a ff ff ff    	jne    120b <su_sprintf+0x82>
    12d1:	90                   	nop
    12d2:	c9                   	leaveq 
    12d3:	c3                   	retq   

00000000000012d4 <int2str>:
    12d4:	f3 0f 1e fa          	endbr64 
    12d8:	55                   	push   %rbp
    12d9:	48 89 e5             	mov    %rsp,%rbp
    12dc:	89 7d ec             	mov    %edi,-0x14(%rbp)
    12df:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    12e3:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
    12ea:	8b 4d ec             	mov    -0x14(%rbp),%ecx
    12ed:	48 63 c1             	movslq %ecx,%rax
    12f0:	48 69 c0 67 66 66 66 	imul   $0x66666667,%rax,%rax
    12f7:	48 c1 e8 20          	shr    $0x20,%rax
    12fb:	89 c2                	mov    %eax,%edx
    12fd:	c1 fa 02             	sar    $0x2,%edx
    1300:	89 c8                	mov    %ecx,%eax
    1302:	c1 f8 1f             	sar    $0x1f,%eax
    1305:	29 c2                	sub    %eax,%edx
    1307:	89 d0                	mov    %edx,%eax
    1309:	c1 e0 02             	shl    $0x2,%eax
    130c:	01 d0                	add    %edx,%eax
    130e:	01 c0                	add    %eax,%eax
    1310:	29 c1                	sub    %eax,%ecx
    1312:	89 ca                	mov    %ecx,%edx
    1314:	89 d0                	mov    %edx,%eax
    1316:	8d 48 30             	lea    0x30(%rax),%ecx
    1319:	8b 45 f8             	mov    -0x8(%rbp),%eax
    131c:	8d 50 01             	lea    0x1(%rax),%edx
    131f:	89 55 f8             	mov    %edx,-0x8(%rbp)
    1322:	48 63 d0             	movslq %eax,%rdx
    1325:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1329:	48 01 d0             	add    %rdx,%rax
    132c:	89 ca                	mov    %ecx,%edx
    132e:	88 10                	mov    %dl,(%rax)
    1330:	8b 45 ec             	mov    -0x14(%rbp),%eax
    1333:	48 63 d0             	movslq %eax,%rdx
    1336:	48 69 d2 67 66 66 66 	imul   $0x66666667,%rdx,%rdx
    133d:	48 c1 ea 20          	shr    $0x20,%rdx
    1341:	c1 fa 02             	sar    $0x2,%edx
    1344:	c1 f8 1f             	sar    $0x1f,%eax
    1347:	29 c2                	sub    %eax,%edx
    1349:	89 d0                	mov    %edx,%eax
    134b:	89 45 ec             	mov    %eax,-0x14(%rbp)
    134e:	83 7d ec 00          	cmpl   $0x0,-0x14(%rbp)
    1352:	75 96                	jne    12ea <int2str+0x16>
    1354:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    135b:	eb 55                	jmp    13b2 <int2str+0xde>
    135d:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1360:	48 63 d0             	movslq %eax,%rdx
    1363:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1367:	48 01 d0             	add    %rdx,%rax
    136a:	0f b6 00             	movzbl (%rax),%eax
    136d:	88 45 f7             	mov    %al,-0x9(%rbp)
    1370:	8b 45 f8             	mov    -0x8(%rbp),%eax
    1373:	2b 45 fc             	sub    -0x4(%rbp),%eax
    1376:	48 98                	cltq   
    1378:	48 8d 50 ff          	lea    -0x1(%rax),%rdx
    137c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1380:	48 01 d0             	add    %rdx,%rax
    1383:	8b 55 fc             	mov    -0x4(%rbp),%edx
    1386:	48 63 ca             	movslq %edx,%rcx
    1389:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
    138d:	48 01 ca             	add    %rcx,%rdx
    1390:	0f b6 00             	movzbl (%rax),%eax
    1393:	88 02                	mov    %al,(%rdx)
    1395:	8b 45 f8             	mov    -0x8(%rbp),%eax
    1398:	2b 45 fc             	sub    -0x4(%rbp),%eax
    139b:	48 98                	cltq   
    139d:	48 8d 50 ff          	lea    -0x1(%rax),%rdx
    13a1:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    13a5:	48 01 c2             	add    %rax,%rdx
    13a8:	0f b6 45 f7          	movzbl -0x9(%rbp),%eax
    13ac:	88 02                	mov    %al,(%rdx)
    13ae:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
    13b2:	8b 45 f8             	mov    -0x8(%rbp),%eax
    13b5:	89 c2                	mov    %eax,%edx
    13b7:	c1 ea 1f             	shr    $0x1f,%edx
    13ba:	01 d0                	add    %edx,%eax
    13bc:	d1 f8                	sar    %eax
    13be:	39 45 fc             	cmp    %eax,-0x4(%rbp)
    13c1:	7c 9a                	jl     135d <int2str+0x89>
    13c3:	8b 45 f8             	mov    -0x8(%rbp),%eax
    13c6:	5d                   	pop    %rbp
    13c7:	c3                   	retq   

00000000000013c8 <main>:
    13c8:	f3 0f 1e fa          	endbr64 
    13cc:	55                   	push   %rbp
    13cd:	48 89 e5             	mov    %rsp,%rbp
    13d0:	48 83 ec 70          	sub    $0x70,%rsp
    13d4:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    13db:	00 00 
    13dd:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    13e1:	31 c0                	xor    %eax,%eax
    13e3:	48 8d 45 90          	lea    -0x70(%rbp),%rax
    13e7:	ba 0a 00 00 00       	mov    $0xa,%edx
    13ec:	48 8d 35 11 0c 00 00 	lea    0xc11(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    13f3:	48 89 c7             	mov    %rax,%rdi
    13f6:	b8 00 00 00 00       	mov    $0x0,%eax
    13fb:	e8 89 fd ff ff       	callq  1189 <su_sprintf>
    1400:	48 8d 45 90          	lea    -0x70(%rbp),%rax
    1404:	48 89 c6             	mov    %rax,%rsi
    1407:	48 8d 3d 02 0c 00 00 	lea    0xc02(%rip),%rdi        # 2010 <_IO_stdin_used+0x10>
    140e:	b8 00 00 00 00       	mov    $0x0,%eax
    1413:	e8 78 fc ff ff       	callq  1090 <printf@plt>
    1418:	48 8d 3d f7 0b 00 00 	lea    0xbf7(%rip),%rdi        # 2016 <_IO_stdin_used+0x16>
    141f:	e8 4c fc ff ff       	callq  1070 <puts@plt>
    1424:	b8 00 00 00 00       	mov    $0x0,%eax
    1429:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
    142d:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
    1434:	00 00 
    1436:	74 05                	je     143d <main+0x75>
    1438:	e8 43 fc ff ff       	callq  1080 <__stack_chk_fail@plt>
    143d:	c9                   	leaveq 
    143e:	c3                   	retq   
    143f:	90                   	nop

0000000000001440 <__libc_csu_init>:
    1440:	f3 0f 1e fa          	endbr64 
    1444:	41 57                	push   %r15
    1446:	4c 8d 3d 5b 29 00 00 	lea    0x295b(%rip),%r15        # 3da8 <__frame_dummy_init_array_entry>
    144d:	41 56                	push   %r14
    144f:	49 89 d6             	mov    %rdx,%r14
    1452:	41 55                	push   %r13
    1454:	49 89 f5             	mov    %rsi,%r13
    1457:	41 54                	push   %r12
    1459:	41 89 fc             	mov    %edi,%r12d
    145c:	55                   	push   %rbp
    145d:	48 8d 2d 4c 29 00 00 	lea    0x294c(%rip),%rbp        # 3db0 <__do_global_dtors_aux_fini_array_entry>
    1464:	53                   	push   %rbx
    1465:	4c 29 fd             	sub    %r15,%rbp
    1468:	48 83 ec 08          	sub    $0x8,%rsp
    146c:	e8 8f fb ff ff       	callq  1000 <_init>
    1471:	48 c1 fd 03          	sar    $0x3,%rbp
    1475:	74 1f                	je     1496 <__libc_csu_init+0x56>
    1477:	31 db                	xor    %ebx,%ebx
    1479:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1480:	4c 89 f2             	mov    %r14,%rdx
    1483:	4c 89 ee             	mov    %r13,%rsi
    1486:	44 89 e7             	mov    %r12d,%edi
    1489:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    148d:	48 83 c3 01          	add    $0x1,%rbx
    1491:	48 39 dd             	cmp    %rbx,%rbp
    1494:	75 ea                	jne    1480 <__libc_csu_init+0x40>
    1496:	48 83 c4 08          	add    $0x8,%rsp
    149a:	5b                   	pop    %rbx
    149b:	5d                   	pop    %rbp
    149c:	41 5c                	pop    %r12
    149e:	41 5d                	pop    %r13
    14a0:	41 5e                	pop    %r14
    14a2:	41 5f                	pop    %r15
    14a4:	c3                   	retq   
    14a5:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    14ac:	00 00 00 00 

00000000000014b0 <__libc_csu_fini>:
    14b0:	f3 0f 1e fa          	endbr64 
    14b4:	c3                   	retq   

Disassembly of section .fini:

00000000000014b8 <_fini>:
    14b8:	f3 0f 1e fa          	endbr64 
    14bc:	48 83 ec 08          	sub    $0x8,%rsp
    14c0:	48 83 c4 08          	add    $0x8,%rsp
    14c4:	c3                   	retq   
