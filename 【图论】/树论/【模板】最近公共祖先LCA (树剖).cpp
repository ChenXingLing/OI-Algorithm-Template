#include<algorithm>
#include<cstdio>
#define Re register int
using namespace std;
const int N=5e5+3;
int n,m,x,y,T,root;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Killed_Tree{
	struct QAQ{int to,next;}a[N<<1];
	int o,head[N];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	int id_o,id[N],fa[N],son[N],top[N],deep[N],size[N];
	inline void dfs1(Re x,Re Fa){
		size[x]=1,deep[x]=deep[fa[x]=Fa]+1;
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=Fa){
				dfs1(to,x);
				size[x]+=size[to];
				if(size[to]>size[son[x]])son[x]=to;
			}
	}
	inline void dfs2(Re x,Re rt){
		id[x]=++id_o,top[x]=rt;
		if(!son[x])return;
		dfs2(son[x],rt);
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=fa[x]&&to!=son[x])dfs2(to,to);
	}
	inline void kill(Re rt){dfs1(rt,0),dfs2(rt,rt);}
	inline int lca(Re x,Re y){
		while(top[x]!=top[y]){
			if(deep[top[x]]<deep[top[y]])swap(x,y);
			x=fa[top[x]];
		}
		if(deep[x]>deep[y])swap(x,y);
		return x;
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),in(root),m=n-1;
	while(m--)in(x),in(y),T1.add(x,y),T1.add(y,x);
	T1.kill(root);
	while(T--)in(x),in(y),printf("%d\n",T1.lca(x,y));
}
