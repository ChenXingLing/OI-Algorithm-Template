#include<bits/stdc++.h>
#include<windows.h>
#define Re register int 
using namespace std;
int main(){
	Re sec=0.1,HYJ=0;//�������ݼ��ʱ�䣬������ÿ 0.1���һ�� 
	sec*=1e3;
    while(1){
    	printf("�� %d �����ݣ�\n",++HYJ);
        system("data.exe>data.in");//���������ӽ��ļ� 
        system("std.exe<data.in>std.out");//�������ݺ���һ��std��� 
        system("myprogram.exe<data.in>my.out");//���������ݲ��ȥ-->���Լ�д����ȫWAȴ�ܹ������ĳ���
        if(system("fc std.out my.out")){//�Ƚϱ�־ָ�� fc������ı���һ���򷵻�1
            system("pause");
			printf("FBI WARNING!!! �����ʰ����ݿ�������\n");
            //break; 
        }
        Sleep(sec);
    }
}
