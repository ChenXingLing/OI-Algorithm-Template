#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=1e4+5,M=1e5+5,inf=2147483647;
int x,y,z,n,m,s,t,st,ed;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Dinic{
	int o,h,t,Q[N],dis[N],cur[N],head[N];LL maxflow;
	Dinic(){o=1;}
	struct QAQ{int to,next,flow;}a[M<<1];
	inline void add_(Re x,Re y,Re flow){a[++o].to=y,a[o].flow=flow,a[o].next=head[x],head[x]=o;}
	inline void add(Re x,Re y,Re flow){add_(x,y,flow),add_(y,x,0);}
	inline int bfs(Re st,Re ed){
		for(Re i=0;i<=ed;++i)dis[i]=0,cur[i]=head[i];
		h=1,t=0,Q[++t]=st,dis[st]=1;
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
	inline void dinic(Re st,Re ed){while(bfs(st,ed))maxflow+=dfs(st,inf);}
}T1;
int main(){
    in(n),in(m),in(s),in(t),st=n+1,ed=st+1;
    while(m--)in(x),in(y),in(z),T1.add(x,y,z);
    T1.add(st,s,inf),T1.add(t,ed,inf),T1.dinic(st,ed);
    printf("%lld",T1.maxflow);
}
