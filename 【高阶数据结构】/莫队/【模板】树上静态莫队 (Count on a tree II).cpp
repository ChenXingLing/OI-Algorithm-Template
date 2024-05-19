#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
using namespace std;
const int N=4e4+3,M=1e5+3,INF=1e6+3,logN=16;
int n,m,o,x,y,T,BL,id_O,b[N],A[N],B[N<<1],head[N],last[N],first[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    Re fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct LCA{
	int deep[N],ant[N][20];
	inline void dfs(Re x,Re fa){
		first[B[++B[0]]=x]=++id_O;
		deep[x]=deep[ant[x][0]=fa]+1;
		for(Re i=1;(1<<i)<=deep[x];++i)ant[x][i]=ant[ant[x][i-1]][i-1];
		for(Re i=head[x];i;i=a[i].next)if(a[i].to!=fa)dfs(a[i].to,x);
		last[B[++B[0]]=x]=++id_O;
	}
	inline int lca(Re x,Re y){
		if(deep[x]<deep[y])swap(x,y);
		for(Re i=logN;i>=0;--i)if(deep[ant[x][i]]>=deep[y])x=ant[x][i];
		if(x==y)return x;
		for(Re i=logN;i>=0;--i)if(ant[x][i]!=ant[y][i])x=ant[x][i],y=ant[y][i];
		return ant[x][0];
	}
}T1;
struct Query{
	int l,r,id,lca;
	inline bool operator<(const Query &O)const{
		Re B1=l/BL,B2=O.l/BL;
		return B1!=B2?B1<B2:((B1&1)?r<O.r:r>O.r);
	}
}Q[M];
int ans,vis[N<<1],Ans[M],cnt[INF];
inline void change(Re x){
	vis[x]?ans-=!--cnt[A[x]]:ans+=!cnt[A[x]]++,vis[x]^=1;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),BL=sqrt(n<<1);
	for(Re i=1;i<=n;++i)in(A[i]),b[i]=A[i];
	sort(b+1,b+n+1),m=unique(b+1,b+n+1)-b-1;
	for(Re i=1;i<=n;++i)A[i]=lower_bound(b+1,b+m+1,A[i])-b;
	m=n-1;while(m--)in(x),in(y),add(x,y),add(y,x);
	T1.dfs(1,0);
	for(Re i=1;i<=T;++i){
		in(x),in(y);Re lca=T1.lca(x,y);
		if(first[x]>first[y])swap(x,y);
		if(lca==x)Q[i]=(Query){first[x],first[y],i,0};
		else Q[i]=(Query){last[x],first[y],i,lca};
	}
	sort(Q+1,Q+T+1);
	Re nowL=1,nowR=0;
	for(Re i=1;i<=T;++i){
		Re L=Q[i].l,R=Q[i].r,lca=Q[i].lca;
		while(nowL<L)change(B[nowL++]);
		while(nowL>L)change(B[--nowL]);
		while(nowR>R)change(B[nowR--]);
		while(nowR<R)change(B[++nowR]);
		if(lca)change(lca);
		Ans[Q[i].id]=ans;
		if(lca)change(lca);
	}
	for(Re i=1;i<=T;++i)printf("%d\n",Ans[i]);
}
