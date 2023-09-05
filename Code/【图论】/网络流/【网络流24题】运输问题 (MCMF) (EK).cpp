#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=205,M=10205,inf=2e9;//µãÊý: 100+100+2=202, ±ßÊý: 100*100+100*2=10200
int o=1,n,m,h,t,st,ed,cyf[N],pan[N],pre[N],dis[N],head[N],Flow[N][2],Cost[N][N];LL mincost,maxflow; 
struct QAQ{int w,to,next,flow;}a[M<<1];queue<int>Q;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z,Re w){a[++o].flow=z,a[o].w=w,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void add_(Re a,Re b,Re flow,Re w){add(a,b,flow,w),add(b,a,0,-w);}
inline int SPFA(Re st,Re ed){
	for(Re i=0;i<=ed;++i)dis[i]=inf,pan[i]=0;
	Q.push(st),pan[st]=1,dis[st]=0,cyf[st]=inf;
	while(!Q.empty()){
		Re x=Q.front();Q.pop();pan[x]=0;
		for(Re i=head[x],to;i;i=a[i].next)
			if(a[i].flow&&dis[to=a[i].to]>dis[x]+a[i].w){
				dis[to]=dis[x]+a[i].w,pre[to]=i;
				cyf[to]=min(cyf[x],a[i].flow);
				if(!pan[to])pan[to]=1,Q.push(to);
			}
	}
	return dis[ed]!=inf;
}
inline void EK(Re st,Re ed){
	while(SPFA(st,ed)){
		Re x=ed;maxflow+=cyf[ed],mincost+=(LL)cyf[ed]*dis[ed];
		while(x!=st){
			Re i=pre[x];
			a[i].flow-=cyf[ed];
			a[i^1].flow+=cyf[ed];
			x=a[i^1].to;
		}
	}
}
int main(){
	in(n),in(m),st=n+m+1,ed=st+1;
	for(Re i=1;i<=n;++i)in(Flow[i][0]),add_(st,i,Flow[i][0],0);
	for(Re i=1;i<=m;++i)in(Flow[i][1]),add_(n+i,ed,Flow[i][1],0);
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=m;++j)
			in(Cost[i][j]),add_(i,n+j,inf,Cost[i][j]);
	EK(st,ed);
	printf("%lld\n",mincost);
	memset(head,0,sizeof(head));
	memset(cyf,0,sizeof(cyf));
	memset(pre,0,sizeof(pre));
	memset(a,0,sizeof(a));
	o=1;maxflow=mincost=0;
	for(Re i=1;i<=n;++i)add_(st,i,Flow[i][0],0);
	for(Re i=1;i<=m;++i)add_(n+i,ed,Flow[i][1],0);
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=m;++j)
			add_(i,n+j,inf,-Cost[i][j]);
	EK(st,ed);
	printf("%lld\n",-mincost);
}
