#include<cstdio>
#define R register int
int n,t,px[10005],pk[10005];
inline void prime_devisor(int x){
	if(x%2==0){
		px[++t]=2;
		while(x%2==0)pk[t]++,x/=2;
	}
	for(R i=3;i*i<=x;i+=2){
		if(x%i==0){
			px[++t]=i;
			while(x%i==0)pk[t]++,x/=i;
		}
	}
	if(x!=1)px[++t]=x,pk[t]=1;
}
inline int sakura(){
	scanf("%d",&n);
	printf("%d=",n);
	prime_devisor(n);
	for(R i=1;i<=t;i++){
		printf("%d^%d",px[i],pk[i]);
		if(i<t)printf("+");
	}
}
int QAQWQ=sakura();
int main(){}
