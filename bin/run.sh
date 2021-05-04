if [ $1 ]; then 
    img=$1
else
    img=suos.img
fi
imgDir="C:/Users/User/Documents/PROGRAM/C/SuOS/img/"
imgPath=$imgDir/$img
qemuDir="/mnt/c/Program Files/qemu/"
qemu=qemu-system-x86_64.exe
#qemuDir=/home/sucicada/PROGRAM/C/30daysOS/tolset/z_tools/qemu
#qemu=qemu.exe
cd "$qemuDir"

./$qemu \
   $imgPath
