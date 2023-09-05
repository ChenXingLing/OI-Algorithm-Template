#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=103,M=503;
int n,m,o,x,y,z,K,ans,pan[N],head[N],dp[N][1024+3];queue<int>Q;
struct QAQ{int w,to,next;}a[M<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void SPFA(Re s){
	while(!Q.empty()){
		Re x=Q.front();Q.pop();pan[x]=0;
		for(Re i=head[x],to;i;i=a[i].next)
			if(dp[x][s]+a[i].w<dp[to=a[i].to][s]){
				dp[to][s]=dp[x][s]+a[i].w;
				if(!pan[to])Q.push(to),pan[to]=1;
			}
	}
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),in(K);
	while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
	memset(dp,63,sizeof(dp));Re inf=dp[0][0];
	for(Re i=1;i<=K;++i)in(x),dp[x][1<<i-1]=0,ans=x;
	Re V=(1<<K)-1;
	for(Re s=0;s<=V;++s){
		for(Re i=1;i<=n;++i){
			for(Re t=(s-1)&s;t;t=(t-1)&s)
				dp[i][s]=min(dp[i][s],dp[i][t]+dp[i][s^t]);
			if(dp[i][s]!=inf)Q.push(i),pan[i]=1;
		}
		SPFA(s);
	}
	printf("%d ",dp[ans][V]);
}
