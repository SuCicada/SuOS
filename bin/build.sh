cd `dirname $0`/..
if [ $1 ];then
    source=$1
else
    source=suos.nas
fi
img=img/suos.img

bin/nask.exe $source $img
echo "私は `pwd` です。"
echo "nask suos.nas ->  $img"
ls -l $img

