#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=3003;
int n,m,x,y,z,o,A[N],V[N],head[N],dp[N][N];
struct QAQ{int w,to,next;}a[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].to=y,a[o].next=head[x],head[x]=o,a[o].w=z;}
inline int dfs(Re x){
	dp[x][0]=0;if(x>=n-m+1)V[x]=1,dp[x][1]=A[x];
	for(Re i=head[x],to;i;i=a[i].next){
		dfs(to=a[i].to);V[x]+=V[to];
		for(Re j=V[x];j;--j)
			for(Re k=1;k<=j&&k<=V[to];++k)
				dp[x][j]=max(dp[x][j],dp[to][k]+dp[x][j-k]-a[i].w);
	}
}
int main(){
	in(n),in(m);
	memset(dp,-127,sizeof(dp));
	for(Re i=1;i<=n-m;++i){in(x);while(x--)in(y),in(z),add(i,y,z);}
	for(Re i=n-m+1;i<=n;++i)in(A[i]);
	dfs(1);
	for(Re i=m;i;--i)if(dp[1][i]>=0){printf("%d",i);break;}
}
