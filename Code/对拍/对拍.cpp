#include<bits/stdc++.h>
#include<windows.h>
#define Re register int 
using namespace std;
int main(){
	Re sec=0.1,HYJ=0;//生成数据间隔时间，这里是每 0.1秒搞一次 
	sec*=1e3;
    while(1){
    	printf("第 %d 组数据：\n",++HYJ);
        system("data.exe>data.in");//生成数据扔进文件 
        system("std.exe<data.in>std.out");//生成数据后跑一遍std标程 
        system("myprogram.exe<data.in>my.out");//用力把数据插进去-->我自己写出的全WA却能过样例的程序
        if(system("fc std.out my.out")){//比较标志指令 fc，如果文本不一样则返回1
            system("pause");
			printf("FBI WARNING!!! 吃柠檬吧数据卡掉了我\n");
            //break; 
        }
        Sleep(sec);
    }
}
