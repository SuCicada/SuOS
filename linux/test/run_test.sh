#!/bin/bash

cd $(dirname $0)
f=$1
out=/tmp/test.out
gcc -m32 $f -o $out && $out 
