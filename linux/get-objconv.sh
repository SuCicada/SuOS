#!/bin/sh

cd $(dirname $0)
mkdir -p lib
cd lib
wget http://www.agner.org/optimize/objconv.zip -O objconv.zip
unzip objconv.zip -d objconv
cd objconv

unzip source.zip -d source
cd source
#./build.sh
g++ -o objconv -O2 *.cpp --trace
mv objconv ../../..//bin/
