#!/bin/bash
# shellcheck disable=SC2046,SC2164,SC2068

cd $(dirname "$0")
export GCC="gcc -m32 "
#shellcheck source=./run_test.sh
./run_test.sh $@
