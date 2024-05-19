#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#include<map>
#define LL long long
#define Re register int
#define mp make_pair
using namespace std;
const int N=5e5+3,M=(N<<2)+N*18*2,P=1e9+7;
int o,n,Ans,head[N<<2];LL X[N],R[N];
struct QAQ{int x,to,next;}a[M];map<pair<int,int>,int>vis;
inline void add(Re x,Re y){a[++o].x=x,a[o].to=y,a[o].next=head[x],head[x]=o;}
template<typename T>inline void in(T &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	int O;
	struct QAQ{int in;}tr[N<<2];
	inline void build(Re p,Re L,Re R){
		if(L==R){tr[p].in=L;return;}
		tr[p].in=++O;
		build(pl,L,mid),build(pr,mid+1,R);
		add(tr[p].in,tr[pl].in),add(tr[p].in,tr[pr].in);
	}
	inline void change(Re p,Re L,Re R,Re l,Re r,Re x){
//		printf("(x=%d) -> (l=%d,r=%d) w=%d\n",x,l,r,w);return;
		if(l<=L&&R<=r){add(x,tr[p].in);return;}
		if(l<=mid)change(pl,L,mid,l,r,x);
		if(r>mid)change(pr,mid+1,R,l,r,x);
	}
}TR;
inline int find1(LL x,Re r){
	Re l=1;
	while(l<r){
		Re Mid=l+r>>1;
		if(X[Mid]<x)l=Mid+1;
		else r=Mid;
	}
	return r;
}
inline int find2(LL x,Re l){
	Re r=n;
	while(l<r){
		Re Mid=l+r+1>>1;
		if(X[Mid]>x)r=Mid-1;
		else l=Mid;
	}
	return l;
}
struct Tuopu{
	int o,n,L[N<<2],R[N<<2],ru[N<<2],pan[N<<2],head[N<<2];queue<int>Q;
	struct QAQ{int to,next;}a[M];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void dfs(Re x){
		if(pan[x])return;
		pan[x]=1;
		for(Re i=head[x],to;i;i=a[i].next)
			dfs(to=a[i].to),L[x]=min(L[x],L[to]),R[x]=max(R[x],R[to]);
	}
	inline void sakura(){for(Re i=1;i<=n;++i)if(!ru[i])dfs(i);}
}T2;
int Q_o,ip[N<<2];
struct Tarjan{
	int n,t,dfn_o,Q[N<<2],low[N<<2],dfn[N<<2],pan[N<<2];
	inline void tarjan(Re x){
		dfn[x]=low[x]=++dfn_o,Q[++t]=x,pan[x]=1;
		for(Re i=head[x],to;i;i=a[i].next)
			if(!dfn[to=a[i].to])tarjan(to),low[x]=min(low[x],low[to]);
			else if(pan[to])low[x]=min(low[x],dfn[to]);
		if(low[x]==dfn[x]){
			++Q_o,T2.L[Q_o]=n+1,T2.R[Q_o]=-1;
			while(1){
				ip[Q[t]]=Q_o,pan[Q[t]]=0;
				if(x==Q[t--])break;
			}
		}
	}
	inline void sakura(){
		for(Re i=1;i<=n;++i)if(!dfn[i])tarjan(i);
		for(Re i=1,x,y;i<=o;++i)
			if((x=ip[a[i].x])!=(y=ip[a[i].to])&&!vis[mp(x,y)])
				vis[mp(x,y)]=1,++T2.ru[y],T2.add(x,y);
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),TR.O=n,TR.build(1,1,n);
	for(Re i=1;i<=n;++i)in(X[i]),in(R[i]);
	for(Re i=1;i<=n;++i)TR.change(1,1,n,find1(X[i]-R[i],i),find2(X[i]+R[i],i),i);
	T1.n=TR.O,T1.sakura();
	for(Re i=1;i<=n;++i)T2.L[ip[i]]=min(T2.L[ip[i]],i),T2.R[ip[i]]=max(T2.R[ip[i]],i);;
	T2.n=Q_o,T2.sakura();
	for(Re i=1;i<=n;++i)(Ans+=(LL)i*(T2.R[ip[i]]-T2.L[ip[i]]+1)%P)%=P;
	printf("%d\n",Ans);
}
