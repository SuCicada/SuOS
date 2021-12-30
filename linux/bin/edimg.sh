#!/bin/bash
# 制作一个 1.44MB 的文件用于作为软盘文件
input=$1
output=$2
# 第一个512B 是程序, 是启动引导程序, 即 suos.nas
dd if="$input" of="$output" bs=512 count=1
# 之后都是空白
dd if=/dev/zero of="$output" bs=512 seek=1 skip=1 count=2879
