#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e6+5,logN=14;
int o,n,m,x,y,t,T,dfn_O,A[N],Q[N],dfn[N],idx[N],Ans[N],cnt[N],son[N],deep[N],size[N],head[N];
struct QAQ{int to,next;}a[N];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
struct Query{
	int o,head[N];
	struct QAQ{int to,id,next;}a[N];
	inline void add(Re x,Re y,Re id){a[++o].to=y,a[o].id=id,a[o].next=head[x],head[x]=o;}
}QT;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct LCA{
	int ant[N][15];
	inline void dfs(Re x,Re fa){
		deep[x]=deep[ant[x][0]=fa]+1;
		for(Re i=1;(1<<i)<=deep[x];++i)ant[x][i]=ant[ant[x][i-1]][i-1];
		for(Re i=head[x];i;i=a[i].next)if(a[i].to!=fa)dfs(a[i].to,x);
	}
	inline int kant(Re x,Re k){
		for(Re i=logN;i>=0;--i)
			if((1<<i)<=k)k-=(1<<i),x=ant[x][i];
		return x;
	}
}T1;
inline void dfs(Re x,Re fa){
	idx[dfn[x]=++dfn_O]=x,size[x]=1,deep[x]=deep[fa]+1;
    for(Re i=head[x],to;i;i=a[i].next)
        if((to=a[i].to)!=fa)dfs(to,x),size[x]+=size[to];
}
inline void CL(){
	while(t)cnt[Q[t--]]=0;
}
inline void insert(Re x){
	++cnt[Q[++t]=deep[x]];
}
inline void addson(Re x,Re fa){
	insert(x);
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa)addson(to,x);
}
inline void getans(Re x){
	for(Re i=QT.head[x];i;i=QT.a[i].next)
		Ans[QT.a[i].id]=cnt[deep[x]+QT.a[i].to];
}
inline void sakura(Re L,Re R){
    if(L==R){if(size[idx[L]]==1)CL(),insert(idx[L]),getans(idx[L]);return;}
    Re mid=L+R>>1;
    sakura(L,mid),sakura(mid+1,R);
    Re p=mid;CL();
    for(Re i=mid,j;i>=L&&(j=i+size[idx[i]]-1)<=R;--i){
        insert(idx[i]);
        if(j<=mid)continue;
        while(p<j)insert(idx[++p]);
        getans(idx[i]);
    }
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T);
	for(Re i=2;i<=n;++i)in(x),add(x,i);
	T1.dfs(1,0);
	for(Re i=1;i<=T;++i)in(x),in(y),QT.add(T1.kant(x,y),y,i);
	dfs(1,0),sakura(1,n);
	for(Re i=1;i<=T;++i)printf("%d ",max(Ans[i]-1,0));
}
