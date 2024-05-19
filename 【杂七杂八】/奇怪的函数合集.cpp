#pragma GCC optimize(2)//O2优化 
#pragma GCC optimize(3,"Ofast","inline")//O3优化 
#pragma once//只编译一次 
#include<windows.h>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cctype>
#include<vector>
#include<string>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define Re register int
using namespace std;
int fu; 
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(fu)x=-x;
}

inline void print_time(){
	printf("time:%lf\n",(double)clock()/(double)CLOCKS_PER_SEC);
}
inline void move_mouse(){
	int sec=0;
	while(sec<50){
		SetCursorPos(rand()%1024,rand()%768);
		Sleep(100);
		sec++;
	}
}

void gotoxy(int x,int y){
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

inline int sakura(){
//	int size = 8 << 20;//手动开栈：8MB
//	char *p = (char*)malloc(size) + size;
//	__asm__("movl %0, %%esp\n" :: "r"(p));

//	Sleep(2000);
	
//	print_time();//输出程序运行时间 
	
//	if(GetAsyncKeyState(VK_UP)){//获取虚拟键使用情况 
//		printf("FBI WARNING!\n");
//		Sleep(2000);
//	}
	
	
//	ios::sync_with_stdio(false);//关闭输入输出流 
	
	
//	srand((int)time(NULL));//关联时间随机函数发射 Biu! Biu! Biu! 
	
//	system("pause");
	
//	system("color 70");
	
//	system("cls");//清空显示框 
	
//	system("pause");
	
//	move_mouse();//改变鼠标指针位置 
	
//	gotoxy(3,3);//将输出栏光标移动至某一位置 
//	printf("BIU! BIU! BIU!\n");
	
}
int QAQWQ=sakura();
int main(){}
