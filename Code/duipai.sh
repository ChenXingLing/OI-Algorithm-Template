#!/bin/bash #������
g++ data.cpp -o data
g++ std.cpp -o std
g++ myprogram.cpp -o myprogram
while true; do
./data>Circuit.in #������������������ض���Circuit.in
./myprogram #�������
./std #��ȷ����
if diff Circuit.out std.out; then #�Ƚ������ļ�
printf AC #��ȷ���AC
else
printf WA #�������WA
#cat Circuit.out std.out #��ʾ�����ļ�
exit 0 #�˳�
fi #����if
done #����while
