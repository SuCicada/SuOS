#!/bin/bash
# 制作一个 1.44MB 的文件用于作为软盘文件
input=$1
kernel=$2
output=$3

block=512

# https://stackoverflow.com/a/2395294
kernel_count=$((($(stat "$kernel" -c%s) + block - 1) / block))
empty_count=$((2880 - 1 - kernel_count))

echo "kernel count $kernel_count"

# 第一个512B 是程序, 是启动引导程序, 即 suos.nas
dd if="$input" of="$output" bs=$block count=1
# 这里是亲自将 kernel 二进制内容写入 img 中, 运行时kernel地址为 0x8200
# 还有一种办法是通过挂载 img, 然后 copy 写入, 这样需要手动确认起始地址, 一般为 0xc400
dd if="$kernel" of="$output" bs=$block seek=1 count=$kernel_count
# 之后都是空白
dd if=/dev/zero of="$output" bs=$block \
  seek=$((1 + kernel_count)) count=$empty_count
