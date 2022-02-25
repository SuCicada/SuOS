#!/bin/bash

# shellcheck disable=SC2046,SC2164,SC2068

cd $(dirname "$0")
f=$1 && shift
GCC=${GCC:-gcc}
server=${SERVER:-false}
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

#  -m32 \
echo "
  GCC: $GCC
"
$GCC \
  -g \
  -O0 \
  $@ \
  "$f" -o $out && {
  echo "================"
  $out
}
cp $out $temp_debug
objdump -S $out_dir/test.out >$out_dir/test.asm

if [ "$server" = "-s" ]; then
  #  tmp_debug_dir=/tmp/CLion/debug
  gdbserver --multi 0.0.0.0:1234 $out
fi
