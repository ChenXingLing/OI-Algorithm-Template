#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=4e4+5,M=7e4+3,inf=2e9;
int x,y,z,o=1,n1,n2,n3,nn,m,h,t,st,ed,Q[N],dis[N],pan[N],pre[N],head[N];long long maxflow; 
struct QAQ{int to,next,flow;}a[M<<1];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].flow=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void add_(Re x,Re y,Re flow){add(x,y,flow),add(y,x,0);}
inline int bfs(Re st,Re ed){
	for(Re i=0;i<=ed;++i)dis[i]=0;
	h=1,t=0,dis[st]=1,Q[++t]=st;
	while(h<=t){
		Re x=Q[h++],to;
		for(Re i=head[x];i;i=a[i].next)
			if(a[i].flow&&!dis[to=a[i].to]){
				dis[to]=dis[x]+1,Q[++t]=to;
				if(to==ed)return 1;
			}
	}
	return 0;
}
inline int dfs(Re x,Re flow){
	if(!flow||x==ed)return flow;
	Re tmp=0,to,f;
	for(Re i=head[x];i;i=a[i].next)
		if(dis[to=a[i].to]==dis[x]+1&&(f=dfs(to,min(flow-tmp,a[i].flow)))){
			a[i].flow-=f,a[i^1].flow+=f,tmp+=f;
			if(!(flow-tmp))break;
		}
	return tmp;
}
inline void Dinic(Re st,Re ed){
	Re flow=0;
	while(bfs(st,ed))while(flow=dfs(st,inf))maxflow+=flow;
}
int main(){
	freopen("123.txt","r",stdin);
	in(n1),in(n2),in(n3);nn=n1+n2+n3,st=nn+n1+1,ed=st+1;
	for(Re i=1;i<=n1;++i)add_(i,i+nn,1);
	for(Re i=1;i<=n2;++i)add_(st,n1+i,1);
	for(Re i=1;i<=n3;++i)add_(n1+n2+i,ed,1);
	in(m);while(m--)in(x),in(y),add_(n1+y,x,1);
	in(m);while(m--)in(x),in(y),add_(x+nn,n1+n2+y,1);
	Dinic(st,ed);
	printf("%lld",maxflow);
}
