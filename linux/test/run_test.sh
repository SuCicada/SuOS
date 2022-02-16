#!/bin/bash

# shellcheck disable=SC2046,SC2164

cd $(dirname "$0")
f=$1
server=$2
out_file=test.out
temp_debug_dir=/tmp/CLion/debug/
#mkdir -p $temp_debug_dir
#out=../output/$out_file
out=$temp_debug_dir/$out_file

# x86_64-w64-mingw32-g++.exe
# -O0  \
# -Wall -Wno-format -Wno-unused -Werror \
# -gstabs
# -march=i486 \
# -std=c99  \
# -static-libgcc \
# -fno-stack-protector \
#  -m32 \
gcc \
  -g \
  "$f" -o $out && $out
if [ "$server" = "-s" ]; then
#  tmp_debug_dir=/tmp/CLion/debug
#  cp $out $tmp_debug_dir/
  gdbserver --multi 0.0.0.0:1234 $out
fi
