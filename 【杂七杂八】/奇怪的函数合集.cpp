#pragma GCC optimize(2)//O2�Ż� 
#pragma GCC optimize(3,"Ofast","inline")//O3�Ż� 
#pragma once//ֻ����һ�� 
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
//	int size = 8 << 20;//�ֶ���ջ��8MB
//	char *p = (char*)malloc(size) + size;
//	__asm__("movl %0, %%esp\n" :: "r"(p));

//	Sleep(2000);
	
//	print_time();//�����������ʱ�� 
	
//	if(GetAsyncKeyState(VK_UP)){//��ȡ�����ʹ����� 
//		printf("FBI WARNING!\n");
//		Sleep(2000);
//	}
	
	
//	ios::sync_with_stdio(false);//�ر���������� 
	
	
//	srand((int)time(NULL));//����ʱ������������� Biu! Biu! Biu! 
	
//	system("pause");
	
//	system("color 70");
	
//	system("cls");//�����ʾ�� 
	
//	system("pause");
	
//	move_mouse();//�ı����ָ��λ�� 
	
//	gotoxy(3,3);//�����������ƶ���ĳһλ�� 
//	printf("BIU! BIU! BIU!\n");
	
}
int QAQWQ=sakura();
int main(){}
