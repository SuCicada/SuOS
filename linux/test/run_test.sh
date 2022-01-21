#!/bin/bash

cd $(dirname $0)
f=$1
server=$2
out=../output/test.out
# x86_64-w64-mingw32-g++.exe
    # -O0  \
    # -Wall -Wno-format -Wno-unused -Werror \
    # -gstabs 
    # -march=i486 \
    # -std=c99  \
    # -static-libgcc \
    # -fno-stack-protector \
gcc \
    -m32 \
     -g  \
    $f -o $out && $out
if [ "$server" = "-s" ]; then
    gdbserver --multi 0.0.0.0:1234 $out
fi
