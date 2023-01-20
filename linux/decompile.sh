#!/bin/bash

SECTIONS="-j .text -j .data -j .rodata"
for name in $@; do
  objdump $SECTIONS -S $name.out > $name.asm
  bin/objconv -fnasm $name.out ${name}2.asm
done
