#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=3e4+3,M=3e4+3;
int n,m,x,y,ans;
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
	inline void CL(){
		memset(bridge,0,sizeof(bridge));
		memset(head,0,sizeof(head));
		memset(low,0,sizeof(low));
		memset(dfn,0,sizeof(dfn));
		dfn_o=ans=0,o=1;
	}
	inline void tarjan(Re x,Re p){
		dfn[x]=low[x]=++dfn_o;
		for(Re i=head[x],to;i;i=a[i].next)
			if(!dfn[to=a[i].to]){
				tarjan(to,i);
				low[x]=min(low[x],low[to]);
				if(low[to]>dfn[x])bridge[i]=bridge[i^1]=1,++ans;
			}
			else if(i!=(p^1))low[x]=min(low[x],dfn[to]);
	}
	inline void get_bridg(){for(Re i=1;i<=n;++i)if(!dfn[i])tarjan(i,-1);}
}T1;
int main(){
    while(scanf("%d%d",&n,&m)&&n&&m){
	    T1.CL();
	    while(m--)in(x),in(y),T1.add(x,y),T1.add(y,x);
	    T1.get_bridg();
	    printf("%d\n",ans);
    }
}
