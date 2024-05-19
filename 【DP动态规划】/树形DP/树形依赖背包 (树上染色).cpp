#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=2003;
int n,m,x,y,z,o,K,size[N],head[N];LL tmp[N],dp[N][N];
struct QAQ{int w,to,next;}a[N<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void dfs(Re x,Re fa){
	size[x]=1,dp[x][0]=dp[x][1]=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa){
			dfs(to,x);
			for(Re j=0;j<=size[x]+size[to];++j)tmp[j]=dp[0][0];
			for(Re j=0;j<=size[x];++j)if(dp[x][j]>=0)
				for(Re k=0;k<=size[to];++k)if(dp[to][k]>=0)
					tmp[j+k]=max(tmp[j+k], dp[x][j]+dp[to][k]+
						(LL)a[i].w*((LL)k*(K-k)+(LL)(size[to]-k)*(n-size[to]-(K-k)))
					);
			size[x]+=size[to];
			for(Re j=0;j<=size[x];++j)dp[x][j]=tmp[j];
		}
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(K),m=n-1;
	while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
	memset(dp,-20,sizeof(dp));
	dfs(1,0),printf("%lld\n",dp[1][K]);
}
