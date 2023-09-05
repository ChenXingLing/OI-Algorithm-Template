#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
const int N=1e7+3;
int i,j,n,cnt,pan[N],miu[N];
inline void get_miu(){
	for(i=1;i<=n;++i)miu[i]=1;
	for(i=2;i<=n;++i)
		if(!pan[i]){
			miu[i]=-1;
			for(j=i<<1;j<=n;j+=i)pan[j]=1,miu[j]*=(j/i%i==0)?0:-1;
		}
}
int main(){
	n=N;
	get_miu();
	for(i=1;i<=n;++i)printf("%d: %d\n",i,miu[i]);
}
