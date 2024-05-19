#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
const int N=1e4+3,M=1e5+3;
int n,m,x,y,Q_o,ans,A[N],ru[N],gs[N],ip[N],dp[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int min(Re a,Re b){return a<b?a:b;}
inline int max(Re a,Re b){return a>b?a:b;}
struct Tarjan{
	int o,t,dfn_o,Q[N],low[N],dfn[N],pan[N],head[N];
	struct QAQ{int x,to,next;}a[M];
	inline void add(Re x,Re y){a[++o].x=x,a[o].to=y,a[o].next=head[x],head[x]=o;}
	inline void tarjan(Re x){
		dfn[x]=low[x]=++dfn_o,Q[++t]=x,pan[x]=1;
		for(Re i=head[x],to;i;i=a[i].next)
			if(!dfn[to=a[i].to])tarjan(to),low[x]=min(low[x],low[to]);
			else if(pan[to])low[x]=min(low[x],dfn[to]);
		if(low[x]==dfn[x]){
			++Q_o;
			while(1){
				ip[Q[t]]=Q_o,gs[Q_o]+=A[Q[t]],pan[Q[t]]=0;
				if(x==Q[t--])break;
			}
		}
	}
	inline void SuoPoint(){for(Re i=1;i<=n;++i)if(!dfn[i])tarjan(i);}
}T1;
struct Tuopu{
	int o,ru[N],pan[N],head[N];std::queue<int>Q;
	struct QAQ{int to,next;}a[M<<1];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void creat(){
		for(Re i=1;i<=T1.o;++i)
			if((x=ip[T1.a[i].x])!=(y=ip[T1.a[i].to]))
				++ru[y],add(x,y);
	}
	inline void tuopu(){
		for(Re i=1;i<=Q_o;++i)if(!ru[i])dp[i]=gs[i],Q.push(i);
		while(!Q.empty()){
			Re x=Q.front();Q.pop();
			for(Re i=head[x],to;i;i=a[i].next){
				to=a[i].to;
				dp[to]=max(dp[to],dp[x]+gs[to]);
				if(!(--ru[to]))Q.push(to);
			}
		}
	}
}T2;
int main(){
	in(n),in(m);
	for(Re i=1;i<=n;++i)in(A[i]);
	while(m--)in(x),in(y),T1.add(x,y);
	T1.SuoPoint(),T2.creat(),T2.tuopu();
	for(Re i=1;i<=Q_o;++i)ans=max(ans,dp[i]);
	printf("%d",ans);
}
