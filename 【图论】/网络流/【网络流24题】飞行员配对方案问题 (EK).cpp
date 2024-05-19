#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=103,inf=2e9;
int x,y,n,m,o=1,h,t,st,ed,ans,maxflow,cyf[N],Q[N],pre[N],pan[N],head[N];
struct QAQ{int to,next,flow;}a[N*N*2+N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].flow=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline int bfs(Re st,Re ed){
	for(Re i=0;i<=n+2;++i)pan[i]=0;
	h=1,t=0,pan[st]=1,cyf[st]=inf,Q[++t]=st;
	while(h<=t){
		Re to,x=Q[h++];
		for(Re i=head[x];i;i=a[i].next)
			if(a[i].flow&&!pan[to=a[i].to]){
				cyf[to]=min(cyf[x],a[i].flow);
				pan[to]=1,pre[to]=i,Q[++t]=to;
				if(to==ed)return 1;
			}
	}
	return 0;
}
inline void EK(Re st,Re ed){
	while(bfs(st,ed)){
		maxflow+=cyf[ed];
		Re x=ed;
		while(x!=st){
			Re i=pre[x];
			a[i].flow-=cyf[ed];
			a[i^1].flow+=cyf[ed];
			x=a[i^1].to;
		}
	}
}
int main(){
	in(m),in(n),st=n+1,ed=n+2;
	while(1){
		in(x),in(y);
		if(x==-1)break;
		add(x,y,1),add(y,x,0);
	}
	for(Re i=1;i<=m;++i)add(st,i,1),add(i,st,0);
	for(Re i=m+1;i<=n;++i)add(i,ed,1),add(ed,i,0);
	EK(st,ed);
	printf("%d\n",maxflow);
	for(Re x=1;x<=m;++x)
		for(Re i=head[x];i;i=a[i].next)
			if(!(i&1)&&a[i].to!=st&&!a[i].flow)printf("%d %d\n",x,a[i].to);
}
