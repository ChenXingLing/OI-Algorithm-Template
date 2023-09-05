#!/bin/bash #背下来
g++ data.cpp -o data
g++ std.cpp -o std
g++ myprogram.cpp -o myprogram
while true; do
./data>Circuit.in #数据生成器输出数据重定向到Circuit.in
./myprogram #待测程序
./std #正确程序
if diff Circuit.out std.out; then #比较两个文件
printf AC #正确输出AC
else
printf WA #错误输出WA
#cat Circuit.out std.out #显示两个文件
exit 0 #退出
fi #结束if
done #结束while
