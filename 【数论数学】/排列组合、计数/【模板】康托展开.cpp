#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
#define LL long long
const int N=1e6+5,P=998244353;
int n,i,ans,a[N],g[N],C[N],jc[N]={1};
inline void add(int x){while(x<=n)++C[x],x+=x&-x;}
inline int ask(int x){
	int ans=0;
	while(x)ans+=C[x],x-=x&-x;
	return ans;
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;++i)scanf("%d",&a[i]);
	for(i=n;i;--i)g[i]=ask(a[i]-1),add(a[i]);
	for(i=1;i<=n;++i)jc[i]=(LL)jc[i-1]*i%P;
	for(i=1;i<=n;++i)(ans+=(LL)g[i]*jc[n-i]%P)%=P;
	printf("%d",ans+1);
}
