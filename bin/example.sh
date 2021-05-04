day=$1

imgDir="C:/Users/User/Documents//PROGRAM/C/30daysOS/projects/$day_day/"
imgPath=$imgDir/$img
cd "/mnt/c/Program Files/qemu/"
./qemu-system-x86_64.exe \
   $imgPath
