#include<algorithm>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=5005,M=5e4+5,inf=2e9;
int x,y,z,w,n,m,s,t,st,ed;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct MCMF{
	int o,h,t,cyf[N],pan[N],pre[N],dis[N],head[N];LL mincost,maxflow;
	MCMF(){o=1;}
	struct QAQ{int w,to,next,flow;}a[M<<1];queue<int>Q;
	inline void add_(Re x,Re y,Re flow,Re w){a[++o].w=w,a[o].to=y,a[o].flow=flow,a[o].next=head[x],head[x]=o;}
	inline void add(Re a,Re b,Re flow,Re w){add_(a,b,flow,w),add_(b,a,0,-w);}
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
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),in(s),in(t),st=n+1,ed=st+1;
	while(m--)in(x),in(y),in(z),in(w),T1.add(x,y,z,w);
	T1.add(st,s,inf,0),T1.add(t,ed,inf,0),T1.EK(st,ed);
	printf("%lld %lld\n",T1.maxflow,T1.mincost);
}
