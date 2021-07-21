#!/bin/bash

input=$1
output=$2
dd if=$input of=$output bs=512 count=1
dd if=/dev/zero of=$output bs=512 seek=1 skip=1 count=2879

