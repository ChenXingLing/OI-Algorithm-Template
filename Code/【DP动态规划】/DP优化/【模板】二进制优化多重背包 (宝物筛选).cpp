#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=103,M=4e4+3;
int n,m,x,y,z,V,ans,v[N*17],w[N*17],dp[M];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
int main(){
	in(m),in(V);
	memset(dp,-127,sizeof(dp));
	dp[0]=0;
	while(m--){
		in(x),in(y),in(z);Re p=1;
		while(z>=p)v[++n]=y*p,w[n]=x*p,z-=p,p<<=1;
		if(z)v[++n]=y*z,w[n]=x*z;
	}
	for(Re i=1;i<=n;++i)
		for(Re j=V;j>=v[i];--j)	
			dp[j]=max(dp[j],dp[j-v[i]]+w[i]);
	for(Re i=0;i<=V;++i)ans=max(ans,dp[i]);
	printf("%d\n",ans);
}
