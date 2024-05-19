#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
const int N=2e6+3,M=2e6+3;
int n,m,p1,p2,x1,x2,Q_o,ip[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Tarjan{
	int o,t,dfn_o,Q[N],low[N],dfn[N],pan[N],head[N];
	struct QAQ{int to,next;}a[M];
	inline int min(Re a,Re b){return a<b?a:b;}
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void tarjan(Re x){
		low[x]=dfn[x]=++dfn_o,Q[++t]=x,pan[x]=1;
		for(Re i=head[x],to;i;i=a[i].next)
			if(!dfn[to=a[i].to])tarjan(to),low[x]=min(low[x],low[to]);
			else if(pan[to])low[x]=min(low[x],dfn[to]);
		if(low[x]==dfn[x]){
			++Q_o;
			while(1){
				ip[Q[t]]=Q_o,pan[Q[t]]=0;
				if(x==Q[t--])break;
			}
		}
	}
	inline void SuoPoint(){for(Re i=1;i<=2*n;++i)if(!dfn[i])tarjan(i);}
}T1;
int main(){
	in(n),in(m);
	while(m--)in(p1),in(x1),in(p2),in(x2),T1.add(p1+(x1^1)*n,p2+x2*n),T1.add(p2+(x2^1)*n,p1+x1*n);
	T1.SuoPoint();
	for(Re i=1;i<=n;++i)if(ip[i]==ip[i+n])return !printf("IMPOSSIBLE");
	puts("POSSIBLE");
	for(Re i=1;i<=n;++i)printf("%d ",ip[i]>ip[i+n]);
}