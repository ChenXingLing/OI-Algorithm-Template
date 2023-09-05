#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,M=1e5+3,logN=17;
int n,m,x,y,o,T,op,id_O,A[N],V[N],W[N],B[N],head[N],last[N],first[N];
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
int BL,TQ,TC,vis[N],cnt[N];LL ans,Ans[M];
struct Query{
	int l,r,id,lca,time;
	inline bool operator<(const Query &O)const{
		Re B1=l/BL,B2=O.l/BL,B3=r/BL,B4=O.r/BL;
		return B1!=B2?B1<B2:(B3!=B4?B3<B4:time<O.time);
	}
}Q[M];
struct Change{int w,co;}C[M];
inline void change(Re x){
	vis[x]?ans-=(LL)V[A[x]]*W[cnt[A[x]]--]:ans+=(LL)V[A[x]]*W[++cnt[A[x]]],vis[x]^=1;
}
int main(){
	freopen("123.txt","r",stdin);
	in(n),in(m),in(T),BL=pow(n<<1,2.0/3.0);
	for(Re i=1;i<=m;++i)in(V[i]);
	for(Re i=1;i<=n;++i)in(W[i]);
	for(Re i=1;i<n;++i)in(x),in(y),add(x,y),add(y,x);
	for(Re i=1;i<=n;++i)in(A[i]);
	T1.dfs(1,0);
	for(Re i=1;i<=T;++i){
		in(op),in(x),in(y);
		if(op){
			Re lca=T1.lca(x,y);
			if(first[x]>first[y])swap(x,y);
			if(lca==x)++TQ,Q[TQ]=(Query){first[x],first[y],TQ,0,TC};
			else ++TQ,Q[TQ]=(Query){last[x],first[y],TQ,lca,TC};
		}
		else C[++TC]=(Change){x,y};
	}
	sort(Q+1,Q+TQ+1);
	Re nowL=1,nowR=0,nowT=0;
	for(Re i=1;i<=TQ;++i){
		Re L=Q[i].l,R=Q[i].r,T=Q[i].time,lca=Q[i].lca;
		while(nowL<L)change(B[nowL++]);
		while(nowL>L)change(B[--nowL]);
		while(nowR>R)change(B[nowR--]);
		while(nowR<R)change(B[++nowR]);
		while(nowT<T){
			Re w=C[++nowT].w;
			if(vis[w])change(w),swap(A[w],C[nowT].co),change(w);
			else swap(A[w],C[nowT].co);
		}
		while(nowT>T){
			Re w=C[nowT].w;
			if(vis[w])change(w),swap(A[w],C[nowT].co),change(w);
			else swap(A[w],C[nowT].co);
			--nowT;
		}
		if(lca)change(lca);
		Ans[Q[i].id]=ans;
		if(lca)change(lca);
	}
	for(Re i=1;i<=TQ;++i)printf("%lld\n",Ans[i]);
}
