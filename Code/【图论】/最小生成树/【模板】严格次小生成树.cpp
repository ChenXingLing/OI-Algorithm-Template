#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=5e5+3,M=5e5+3,logN=19,inf=2e9;
int T,n,m,o,root,fa[N],head[N],Tree[M],M1[N][23],M2[N][23];LL MinTree;
struct QAQ{int w,to,next;}a[M<<1];
struct QWQ{int x,y,w;inline bool operator<(QWQ O)const{return w<O.w;}}A[M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
struct LCA{
	int deep[N],ant[N][23];
	inline void dfs(Re x,Re fa){
		deep[x]=deep[fa]+1,ant[x][0]=fa;
		for(Re i=1;(1<<i)<=deep[x];++i){
			ant[x][i]=ant[ant[x][i-1]][i-1];
			M1[x][i]=max(M1[x][i-1],M1[ant[x][i-1]][i-1]);
			M2[x][i]=max(M2[x][i-1],M2[ant[x][i-1]][i-1]);
			if(M1[x][i-1]!=M1[ant[x][i-1]][i-1])
				M2[x][i]=max(M2[x][i],min(M1[x][i-1],M1[ant[x][i-1]][i-1]));
		}
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=fa)M1[to][0]=a[i].w,M2[to][0]=-inf,dfs(to,x);
	}
	inline int lca(Re x,Re y){
		if(deep[x]>deep[y])swap(x,y);
		for(Re i=logN;i>=0;--i)if(deep[x]<=deep[y]-(1<<i))y=ant[y][i];
		if(x==y)return y;
		for(Re i=logN;i>=0;--i)
			if(ant[x][i]^ant[y][i])x=ant[x][i],y=ant[y][i];
		return ant[x][0];
	}
	inline int ask_max(Re x,Re Ant,Re w){
		Re ans=-inf;
		for(Re i=logN;i>=0;--i)
			if(deep[ant[x][i]]>=deep[Ant]){
				if(w!=M1[x][i])ans=max(ans,M1[x][i]);
				else ans=max(ans,M2[x][i]);
				x=ant[x][i];
			}
		return ans;
	}
}T1;
inline int find(Re x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline void kruscal(){
	sort(A+1,A+m+1);
	for(Re i=1;i<=n;++i)fa[i]=i;
	for(Re i=1;i<=m;++i){
		Re x=A[i].x,y=A[i].y,w=A[i].w;
		if(find(x)!=find(y)){
			MinTree+=w,Tree[i]=1;
			add(x,y,w),add(y,x,w);
			fa[find(x)]=find(y);
		}
	}
}
int main(){
	in(n),in(m),root=1;
	for(Re i=1;i<=m;++i)in(A[i].x),in(A[i].y),in(A[i].w);
	kruscal();
	M1[root][0]=0,M2[root][0]=-inf,T1.dfs(root,0);
	LL ans=1e17;
	for(Re i=1;i<=m;++i)
		if(!Tree[i]){
			Re x=A[i].x,y=A[i].y,w=A[i].w;
			Re lca=T1.lca(x,y);
			ans=min(ans,MinTree+w-max(T1.ask_max(x,lca,w),T1.ask_max(y,lca,w)));
		}
	printf("%lld",ans);
}
