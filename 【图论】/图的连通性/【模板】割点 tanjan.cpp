#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
const int N=2e4+3,M=2e5+3;
int n,m,x,y,ans,cut[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Cut_Point{
	int o,dfn_o,low[N],dfn[N],head[N];
	struct QAQ{int to,next;}a[M];
	inline int min(Re a,Re b){return a<b?a:b;}
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void tarjan(Re x,Re root){
		Re son=0;dfn[x]=low[x]=++dfn_o;
		for(Re i=head[x],to;i;i=a[i].next)
			if(!dfn[to=a[i].to]){
				tarjan(to,root),++son;
				low[x]=min(low[x],low[to]);
				cut[x]|=(x!=root&&low[to]>=dfn[x]);
			}
			else low[x]=min(low[x],dfn[to]);
		cut[x]|=(x==root&&son>1),ans+=cut[x];
	}
	inline void cut_point(){
		for(Re i=1;i<=n;++i)if(!dfn[i])tarjan(i,i);
	}
}T1;
int main(){
	in(n),in(m);
	while(m--)in(x),in(y),T1.add(x,y),T1.add(y,x);
	T1.cut_point();
	printf("%d\n",ans);
	for(Re i=1;i<=n;++i)if(cut[i])printf("%d ",i);
}