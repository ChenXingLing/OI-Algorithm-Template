#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=1e4+3,M=1e5+3,inf=2e9;
int x,y,z,o=1,n,m,h,t,st,ed,Q[N],cyf[N],pan[N],pre[N],head[N];long long maxflow; 
struct QAQ{int to,next,flow;}a[M<<1];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].flow=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline int bfs(Re st,Re ed){
	for(Re i=0;i<=n;++i)pan[i]=0;
	h=1,t=0,pan[st]=1,Q[++t]=st,cyf[st]=inf;
	while(h<=t){
		Re x=Q[h++];
		for(Re i=head[x],to;i;i=a[i].next)
			if(a[i].flow&&!pan[to=a[i].to]){
				cyf[to]=min(cyf[x],a[i].flow);
				Q[++t]=to,pre[to]=i,pan[to]=1;
				if(to==ed)return 1;
			}
	}
	return 0;
}
inline void EK(Re st,Re ed){
	while(bfs(st,ed)==1){
		Re x=ed;maxflow+=cyf[ed];
		while(x!=st){
			Re i=pre[x];
			a[i].flow-=cyf[ed];
			a[i^1].flow+=cyf[ed];
			x=a[i^1].to;
		}
	}
}
int main(){
	in(n),in(m),in(st),in(ed);
	while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,0);
	EK(st,ed);
	printf("%lld",maxflow);
}
