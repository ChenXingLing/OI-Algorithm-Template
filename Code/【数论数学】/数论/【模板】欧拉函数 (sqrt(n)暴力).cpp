#include<cstdio>
#define Re register int
int n;
inline int phi(Re x){
	Re ans=x;
	for(Re i=2;i*i<=x;i++)
		if(x%i==0){
			ans/=i,ans*=i-1;
			while(x%i==0)x/=i;
		}
	if(x>1)ans/=x,ans*=x-1;
	return ans;
}
int main(){
	scanf("%d",&n),printf("%d\n",phi(n));
}
