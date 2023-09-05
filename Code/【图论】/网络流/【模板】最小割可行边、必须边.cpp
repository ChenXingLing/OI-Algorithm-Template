#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=4003,M=6e4+3,inf=2e9;
int n,m,x,y,z,st,ed;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Dinic{
	int o,h,t,Q[N],dis[N],cur[N],head[N];
	struct QAQ{int to,next,flow;}a[M<<1];
	inline void add_(Re x,Re y,Re flow){a[++o].to=y,a[o].flow=flow,a[o].next=head[x],head[x]=o;}
	inline void add(Re x,Re y,Re flow){add_(x,y,flow),add_(y,x,0);}
	inline int bfs(Re st,Re ed){
		for(Re i=0;i<=n;++i)dis[i]=0,cur[i]=head[i];
		h=1,t=0,dis[st]=1,Q[++t]=st;
		while(h<=t){
			Re x=Q[h++];
			for(Re i=head[x],to;i;i=a[i].next)
				if(a[i].flow&&!dis[to=a[i].to]){
					dis[to]=dis[x]+1,Q[++t]=to;
					if(to==ed)return 1;
				}
		}
		return 0;
	}
	inline int dfs(Re x,Re flow){
		if(x==ed||!flow)return flow;
		Re tmp=0,to,f;
		for(Re i=cur[x];i;i=a[i].next){
			cur[x]=i;
			if(dis[to=a[i].to]==dis[x]+1&&(f=dfs(to,min(flow-tmp,a[i].flow)))){
				a[i].flow-=f,a[i^1].flow+=f,tmp+=f;
				if(flow==tmp)break;
			}
		}
		return tmp;
	}
	int Q_o,dfn_O,ip[N],dfn[N],low[N],pan[N];
	inline void tarjan(Re x){
		dfn[x]=low[x]=++dfn_O,Q[++t]=x,pan[x]=1;
		for(Re i=head[x],to;i;i=a[i].next)
			if(a[i].flow){
				if(!dfn[to=a[i].to])tarjan(to),low[x]=min(low[x],low[to]);
				else if(pan[to])low[x]=min(low[x],dfn[to]);
			}
		if(dfn[x]==low[x]){
			++Q_o;
			while(1){
				ip[Q[t]]=Q_o,pan[Q[t]]=0;
				if(x==Q[t--])break;
			}
		}
	}
	inline void sakura(){
		while(bfs(st,ed))dfs(st,inf);
		for(Re i=1;i<=n;++i)if(!dfn[i])tarjan(i);
		for(Re i=2;i<=o;i+=2)printf("%d %d\n",
			(!a[i].flow&&ip[a[i^1].to]!=ip[a[i].to]),
			(!a[i].flow&&ip[st]==ip[a[i^1].to]&&ip[a[i].to]==ip[ed]));
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),in(st),in(ed),T1.o=1;
	while(m--)in(x),in(y),in(z),T1.add(x,y,z);
	T1.sakura();
}
