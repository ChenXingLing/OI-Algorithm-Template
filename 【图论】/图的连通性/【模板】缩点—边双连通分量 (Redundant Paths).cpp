#include<algorithm>
#include<cstdio>
#define Re register int
using namespace std;
const int N=5003,M=10003;
int n,m,x,y,Q_o,leaf,ip[N],du[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Tarjan{
	int o,dfn_o,dfn[N],low[N],head[N],bridge[M<<1];
	struct QAQ{int to,next;}a[M<<1];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void tarjan(Re x,Re p){
		dfn[x]=low[x]=++dfn_o;
		for(Re i=head[x],to;i;i=a[i].next)
			if(!dfn[to=a[i].to]){
				tarjan(to,i);
				low[x]=min(low[x],low[to]);
				if(low[to]>dfn[x])bridge[i]=bridge[i^1]=1;
			}
			else if(i!=(p^1))low[x]=min(low[x],dfn[to]);
	}
	inline void dfs(Re x){
		ip[x]=Q_o;
		for(Re i=head[x];i;i=a[i].next)
			if(!ip[a[i].to]&&!bridge[i])dfs(a[i].to);
	}
	inline void SuoPoint(){
		for(Re i=1;i<=n;++i)if(!dfn[i])tarjan(i,-1);
		for(Re i=1;i<=n;++i)if(!ip[i])++Q_o,dfs(i);
	}
}T1;
int main(){
    in(n),in(m),T1.o=1;
    while(m--)in(x),in(y),T1.add(x,y),T1.add(y,x);
    T1.SuoPoint();
    for(Re i=2;i<=T1.o;i+=2)
    	if((x=ip[T1.a[i].to])!=(y=ip[T1.a[i^1].to]))++du[x],++du[y];
    for(Re i=1;i<=Q_o;++i)leaf+=(du[i]==1);
    printf("%d",leaf+1>>1);
}
