#include<cstdio>
#include<cmath>
int x;
inline bool judge(int n){
	if(n<4)return 1;
	if(n%2==0)return 0;
	int half=sqrt(n);
	for(int i=3;i<=half;i+=2)
		if(n%i==0)return 0;
	return 1;
}
int main(){
	scanf("%d",&x);
	puts(judge(x)?"YES":"NO");
}
