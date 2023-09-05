#include<algorithm>
#include<cstdio>
#define pl tr[p].lp 
#define pr tr[p].rp
#define mid (L+R>>1)
#define Re register int
const int N=3e5+3,logN=19;
int x,y,n,m,T,o,lca,w[N],pt[N],ans[N],head[N],deep[N];
struct QWQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    x=0;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
struct Segmemt_Tree{
	struct QAQ{int g,lp,rp;}tr[N*36];int cnt;
	inline void change(Re &p,Re L,Re R,Re x,Re v){
		if(!p)p=++cnt;
		if(L==R){tr[p].g+=v;return;}
		if(x<=mid)change(pl,L,mid,x,v);
	    else change(pr,mid+1,R,x,v);
	}
	inline int merge(Re p,Re q){
	    if(!p)return q;if(!q)return p;
	    tr[p].g+=tr[q].g;
	    pl=merge(pl,tr[q].lp);
		pr=merge(pr,tr[q].rp);
	    return p;
	}
	inline int ask(Re p,Re L,Re R,Re x){
	    if(!p)return 0;
	    if(L==R)return tr[p].g;
	    if(x<=mid)return ask(pl,L,mid,x);
	    else return ask(pr,mid+1,R,x);
	}
}T1;
struct LCA{
	int ant[N][23];
	inline void dfs(Re x,Re fa){
		deep[x]=deep[fa]+1,ant[x][0]=fa;
		for(Re i=1;(1<<i)<=deep[x];++i)ant[x][i]=ant[ant[x][i-1]][i-1];
		for(Re i=head[x];i;i=a[i].next)if(a[i].to!=fa)dfs(a[i].to,x);
	}
	inline int lca(Re x,Re y){
		if(deep[x]>deep[y])std::swap(x,y);
		for(Re i=logN;i>=0;--i)if(deep[x]<=deep[y]-(1<<i))y=ant[y][i];
		if(x==y)return y;
		for(Re i=logN;i>=0;--i)
			if(ant[x][i]==ant[y][i])continue;
			else x=ant[x][i],y=ant[y][i];
		return ant[x][0];
	}
}T2;
inline void dfs(Re x,Re fa){
    for(Re i=head[x],to;i;i=a[i].next)
    	if((to=a[i].to)!=fa)
        	dfs(to,x),pt[x]=T1.merge(pt[x],pt[to]);
	ans[x]+=T1.ask(pt[x],1,n<<1,n+deep[x]-w[x]);
    if(w[x]&&deep[x]+w[x]<=n)ans[x]+=T1.ask(pt[x],1,n<<1,n+deep[x]+w[x]);
}
int main(){
	in(n),in(T),m=n-1;
	while(m--)in(x),in(y),add(x,y),add(y,x);
	for(Re i=1;i<=n;++i)in(w[i]);
	T2.dfs(1,0);
	while(T--){
		in(x),in(y),lca=T2.lca(x,y);
		T1.change(pt[x],1,n<<1,n+deep[x],1);
        T1.change(pt[y],1,n<<1,n+deep[lca]*2-deep[x],1);
        T1.change(pt[lca],1,n<<1,n+deep[x],-1);
        T1.change(pt[T2.ant[lca][0]],1,n<<1,n+deep[lca]*2-deep[x],-1);
	}
	dfs(1,0);
	for(Re i=1;i<=n;++i)printf("%d ",ans[i]);
}
