#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,inf=2e9,logN=17;
int n,m,o,x,y,T,op,lastans,A[N],deep[N],head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct LCA{
	int fa[N],top[N],son[N],size[N];
	inline void dfs1(Re x,Re Fa){
		size[x]=1,deep[x]=deep[fa[x]=Fa]+1;
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=Fa){
				dfs1(to,x),size[x]+=size[to];
				if(size[son[x]]<size[to])son[x]=to;
			}
	}
	inline void dfs2(Re x,Re rt){
		top[x]=rt;
		if(!son[x])return;
		dfs2(son[x],rt);
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=fa[x]&&to!=son[x])dfs2(to,to);
	}
	inline void build(){dfs1(1,0),dfs2(1,1);}
	inline int lca(Re x,Re y){
		while(top[x]!=top[y]){
			if(deep[top[x]]<deep[top[y]])swap(x,y);
			x=fa[top[x]];
		}
		if(deep[x]>deep[y])swap(x,y);
		return x;
	}
}T1;
inline int Dis(Re x,Re y){return deep[x]+deep[y]-(deep[T1.lca(x,y)]<<1);}//查询原树中点x,y的距离
struct BIT{
	int n;vector<int>C;
	inline void build(Re N){C.resize((n=N)+1);}//使用到的上限为n,空间开n+1
	inline void add(Re x,Re v){++x;while(x<=n)C[x]+=v,x+=x&-x;}//由于dis可能为0,所以在BIT里面统计向后移一位，查询同理
	inline int ask(Re x){++x,x=min(x,n);Re ans=0;while(x)ans+=C[x],x-=x&-x;return ans;}//注意要和维护的上界取最小值，防止越界
}TR1[N],TR2[N];
int rt,sum,fa[N],vis[N],maxp[N],size[N];
inline void getrt(Re x,Re fa){//获取该连通块的重心
	size[x]=1,maxp[x]=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)
			getrt(to,x),size[x]+=size[to],maxp[x]=max(maxp[x],size[to]);
	maxp[x]=max(maxp[x],sum-size[x]);
	if(maxp[x]<maxp[rt])rt=x;
}
inline void sakura(Re x,Re Fa){//处理重心x所囊括的连通块
	Re now=sum;vis[x]=1,fa[x]=Fa;
	TR1[x].build(now/2+1),TR2[x].build(now+1);//由重心性质可知,TR1会使用[0,now/2],TR2会使用[1,now]，向后移一位变为[1,now/2+1]和[2,now+1]
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to])
			sum=size[to]>size[x]?now-size[x]:size[to],maxp[rt=0]=inf,getrt(to,0),sakura(rt,x);//注意子连通块大小不要直接用size[to]
}
inline void change(Re x,Re v){
	TR1[x].add(0,v);//subtree(x)
	for(Re i=x;fa[i];i=fa[i]){//在虚树上面跳父亲 
		Re tmp=Dis(x,fa[i]);
		TR1[fa[i]].add(tmp,v);
		TR2[i].add(tmp,v);
	}
}
inline int ask(Re x,Re K){
	Re ans=TR1[x].ask(K);//subtree(x)
	for(Re i=x;fa[i];i=fa[i]){//在虚树上面跳父亲 
		Re tmp=Dis(x,fa[i]);if(tmp>K)continue;
		ans+=TR1[fa[i]].ask(K-tmp);
		ans-=TR2[i].ask(K-tmp);
	}
	return ans;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),m=n-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	while(m--)in(x),in(y),add(x,y),add(y,x);
	T1.build(),sum=n,maxp[rt=0]=inf,getrt(1,0),sakura(rt,0);
	for(Re i=1;i<=n;++i)change(i,A[i]);
	while(T--){
		in(op),in(x),in(y),x^=lastans,y^=lastans;
		if(op)change(x,y-A[x]),A[x]=y;
		else printf("%d\n",lastans=ask(x,y));
	}
}
