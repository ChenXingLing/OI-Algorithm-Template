#include<cstdio>
#define R register int
int pri[10005],pan[10005],gs;
inline void creat_prime(){
	for(R i=2;i<=10000;i++)
		if(pan[i]==0){
			pri[++gs]=i;
			for(R j=2;i*j<=10000;j++)pan[i*j]=1;
		}
}
inline int sakura(){
	creat_prime();
	for(R i=1;i<=gs;i++)printf("%d\n",pri[i]);
}
int QAQWQ=sakura();
int main(){}
