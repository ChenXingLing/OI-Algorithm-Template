#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e4+3,M=103,INF=1e7+3,inf=2e9;
int n,m,o,x,y,z,T,maxK,K[M],Ans[M],head[N];
struct QAQ{int w,to,next;}a[N<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int rt,sum,dd[N],vis[N],tmp[N],dis[N],maxp[N],size[N];bool judge[INF];
inline void getrt(Re x,Re fa){
	size[x]=1,maxp[x]=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)
			getrt(to,x),size[x]+=size[to],maxp[x]=max(maxp[x],size[to]);
	maxp[x]=max(maxp[x],sum-size[x]);
	if(maxp[x]<maxp[rt])rt=x;
}
inline void getdis(Re x,Re fa,Re w){
	if(dis[fa]+w>maxK)return;
	dd[++dd[0]]=dis[x]=dis[fa]+w;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)getdis(to,x,a[i].w);
}
inline void calc(Re x){
	tmp[0]=0,judge[tmp[++tmp[0]]=0]=1;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]){
			dis[x]=dd[0]=0,getdis(to,x,a[i].w);
			for(Re j=1;j<=dd[0];++j)
				for(Re k=1;k<=T;++k)
					if(K[k]>=dd[j])Ans[k]|=judge[K[k]-dd[j]];
			for(Re j=1;j<=dd[0];++j)judge[tmp[++tmp[0]]=dd[j]]=1;
		}
	for(Re i=1;i<=tmp[0];++i)judge[tmp[i]]=0;
}
inline void sakura(Re x){
	Re now=sum;vis[x]=1,calc(x);//注意一定要开一个局部变量记录当前连通块大小
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to])
			sum=size[to]>size[x]?now-size[x]:size[to],maxp[rt=0]=inf,getrt(to,x),sakura(rt);//注意不能直接取size[to]
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),m=n-1;
	while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
	for(Re i=1;i<=T;++i)in(K[i]),maxK=max(maxK,K[i]);
	sum=n,maxp[rt=0]=inf,getrt(1,0),sakura(rt);
	for(Re i=1;i<=T;++i)puts(Ans[i]?"AYE":"NAY");
}
