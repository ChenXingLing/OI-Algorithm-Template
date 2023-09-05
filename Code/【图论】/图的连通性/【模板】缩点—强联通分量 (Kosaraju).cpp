#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
const int N=1e6+3,M=1e6+3;
int n,m,Q_o,ans,X[M],Y[M],A[N],ip[N],gs[N],dp[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int max(Re a,Re b){return a>b?a:b;}
struct Kosaraju{
	int o,ndfn_o,nQ[N],pan[N],head[N];
	struct QAQ{int x,to,next;}a[M<<1];
	inline void add(Re x,Re y){a[++o].x=x,a[o].to=y,a[o].next=head[x],head[x]=o;}
	inline void dfs1(Re x){
		pan[x]=1;
		for(Re i=head[x];i;i=a[i].next)if(!pan[a[i].to])dfs1(a[i].to);
		nQ[++ndfn_o]=x;
	}
	inline void dfs2(Re x){
		ip[x]=Q_o,gs[Q_o]+=A[x];
		for(Re i=head[x];i;i=a[i].next)if(!ip[a[i].to])dfs2(a[i].to);
	}
	inline void kosaraju(){
		for(Re i=1;i<=m;++i)add(X[i],Y[i]);
		for(Re i=1;i<=n;++i)if(!pan[i])dfs1(i);//ÅÜÄædfsÐò
		memset(head,0,sizeof(head));
		memset(pan,0,sizeof(pan));
		memset(a,0,sizeof(a));o=0;
		for(Re i=1;i<=m;++i)add(Y[i],X[i]);//½¨·´Í¼
		for(Re i=ndfn_o;i;--i)if(!ip[nQ[i]])++Q_o,dfs2(nQ[i]);//Ëõµã
	}
}T1;
struct Tuopu{
	int o,x,y,ru[N],pan[N],head[N];std::queue<int>Q;
	struct QAQ{int to,next;}a[M<<1];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void creat(){
		for(Re i=1;i<=T1.o;++i)
			if((x=ip[T1.a[i].x])!=(y=ip[T1.a[i].to]))
				++ru[y],add(x,y);
	}
	inline void tuopu(){
		creat();
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
	for(Re i=1;i<=m;++i)in(X[i]),in(Y[i]);
	T1.kosaraju(),T2.tuopu();
	for(Re i=1;i<=Q_o;++i)ans=max(ans,dp[i]);
	printf("%d",ans);
}
