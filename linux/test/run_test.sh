#!/bin/bash

# shellcheck disable=SC2046,SC2164

cd $(dirname "$0")
f=$1
server=$2
out_file=test.out
out_dir=../output/

out=$out_dir/$out_file

temp_debug_dir=/tmp/CLion/debug/
temp_debug=$temp_debug_dir/$out_file
mkdir -p $temp_debug_dir

# x86_64-w64-mingw32-g++.exe
# -O0  \
# -Wall -Wno-format -Wno-unused -Werror \
# -gstabs
# -march=i486 \
# -std=c99  \
# -static-libgcc \
# -fno-stack-protector \
#  -m32 \

cp $out $temp_debug

#  -m32 \
gcc \
  -g \
  "$f" -o $out && $out


if [ "$server" = "-s" ]; then
  #  tmp_debug_dir=/tmp/CLion/debug
  gdbserver --multi 0.0.0.0:1234 $out
fi
