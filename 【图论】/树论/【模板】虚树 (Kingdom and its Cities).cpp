#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,logN=17;
int n,m,x,y,o,T,dfn_o,dfn[N],deep[N],head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct LCA{
	int ant[N][20];
	inline void dfs(Re x,Re fa){
		deep[x]=deep[ant[x][0]=fa]+1,dfn[x]=++dfn_o;
		for(Re j=1;(1<<j)<=deep[x];++j)ant[x][j]=ant[ant[x][j-1]][j-1];
		for(Re i=head[x];i;i=a[i].next)if(a[i].to!=fa)dfs(a[i].to,x);
	}
	inline int lca(Re x,Re y){
		if(deep[x]<deep[y])swap(x,y);
		for(Re j=logN;j>=0;--j)if(deep[ant[x][j]]>=deep[y])x=ant[x][j];
		if(x==y)return x;
		for(Re j=logN;j>=0;--j)if(ant[x][j]!=ant[y][j])x=ant[x][j],y=ant[y][j];
		return ant[x][0];
	}
}T1;
inline bool cmp(Re x,Re y){return dfn[x]<dfn[y];}
struct Virtual_Tree{
	int t,o,ans,A[N],Q[N],key[N],head[N];
	struct QAQ{int to,next;}a[N<<1];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void insert(Re x){//虚树构造
		Re lca=T1.lca(Q[t],x);
		while(t>1&&deep[Q[t-1]]>deep[lca])add(Q[t-1],Q[t]),--t;
		if(t&&deep[Q[t]]>deep[lca])add(lca,Q[t--]);
		if(!t||Q[t]!=lca)Q[++t]=lca;
		Q[++t]=x;
	}
	inline void dfs(Re x){//遍历虚树
		if(key[x])//如果x是关键点
			for(Re i=head[x],to;i;i=a[i].next){
				dfs(to=a[i].to);
				if(key[to])key[to]=0,++ans;
			}
		else{//如果x不是关键点
			for(Re i=head[x],to;i;i=a[i].next)
				dfs(to=a[i].to),key[x]+=key[to],key[to]=0;
			if(key[x]>1)key[x]=0,++ans;
		}
		head[x]=0;
	}
	inline void sakura(){
		in(m);Re flag=1;ans=o=t=0;
		for(Re i=1;i<=m;++i)in(A[i]),key[A[i]]=1;
		for(Re i=1;i<=m&&flag;++i)flag&=(!key[T1.ant[A[i]][0]]);
		if(!flag){
			for(Re i=1;i<=m;++i)key[A[i]]=0;
			puts("-1");return;
		}
		sort(A+1,A+m+1,cmp),Q[++t]=1;
		for(Re i=1+(A[1]==1);i<=m;++i)insert(A[i]);
		while(t>1)add(Q[t-1],Q[t]),--t;
		dfs(1),key[1]=0;//根节点可能没有还清除
		printf("%d\n",ans);
	}
}T2;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),m=n-1;
	while(m--)in(x),in(y),add(x,y),add(y,x);
	T1.dfs(1,0),in(T);
	while(T--)T2.sakura();
}
