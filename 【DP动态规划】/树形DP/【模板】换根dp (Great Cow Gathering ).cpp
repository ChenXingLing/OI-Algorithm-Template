#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const LL N=1e5+3,inf=1e18;
int n,m,x,y,z,o,A[N],S[N],dis[N],size[N],head[N];LL ans=inf,f[N],g[N];
struct QAQ{int w,to,next;}a[N<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
//dis[x]: x到fa[x]这条边的边权
//S[x]: x子树内（包含x）所有点的点权之和
//size[x]: x子树内（包含x）节点个数
//f[x]: x子树内（不包含x）所有点的 "到x的距离 乘以 自身点权" 之和
//g[x]: x子树外（不包含x）所有点的 "到x的距离 乘以 自身点权" 之和
inline void dfs1(Re x,Re fa){
	size[x]=1,S[x]=A[x];
	for(Re i=head[x],to;i;i=a[i].next)if((to=a[i].to)!=fa)
		dis[to]=a[i].w,dfs1(to,x),S[x]+=S[to],size[x]+=size[to],f[x]+=f[to]+(LL)S[to]*a[i].w;
}
inline void dfs2(Re x,Re fa){
	if(fa)g[x]=g[fa]+f[fa]-f[x]-(LL)S[x]*dis[x]+(LL)(S[1]-S[x])*dis[x];
	for(Re i=head[x],to;i;i=a[i].next)if((to=a[i].to)!=fa)dfs2(to,x);
	ans=min(ans,f[x]+g[x]);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),m=n-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
	dfs1(1,0),dfs2(1,0),printf("%lld\n",ans);
}
