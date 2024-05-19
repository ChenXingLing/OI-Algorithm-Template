#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=2e5+3,INF=1e6+3,inf=2e9;
int n,m,o,x,y,z,K,Ans,head[N];
struct QAQ{int w,to,next;}a[N<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int rt,sum,dd[N],ddd[N],dep[N],Min[INF],tmp[N],dis[N],vis[N],maxp[N],size[N];
inline void getrt(Re x,Re fa){
	size[x]=1,maxp[x]=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)
			getrt(to,x),size[x]+=size[to],maxp[x]=max(maxp[x],size[to]);
	maxp[x]=max(maxp[x],sum-size[x]);
	if(maxp[x]<maxp[rt])rt=x;
}
inline void getdis(Re x,Re fa,Re w){
	if(dis[fa]+w>K)return;
	dd[++dd[0]]=dis[x]=dis[fa]+w,ddd[dd[0]]=dep[x]=dep[fa]+1;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)getdis(to,x,a[i].w);
}
inline void calc(Re x){
	dis[x]=dep[x]=tmp[0]=0,Min[tmp[++tmp[0]]=0]=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]){
			dd[0]=0,getdis(to,x,a[i].w);
			for(Re i=1;i<=dd[0];++i)Ans=min(Ans,ddd[i]+Min[K-dd[i]]);
			for(Re i=1;i<=dd[0];++i)Min[dd[i]]=min(Min[dd[i]],ddd[i]),tmp[++tmp[0]]=dd[i];
		}
	for(Re i=1;i<=tmp[0];++i)Min[tmp[i]]=inf;
}
inline void sakura(Re x){
	Re now=sum;vis[x]=1,calc(x);
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to])
			sum=size[to]>size[x]?now-size[x]:size[to],maxp[rt=0]=inf,getrt(to,x),sakura(rt);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(K),m=n-1;
	for(Re i=0;i<=K;++i)Min[i]=inf;
	while(m--)in(x),in(y),in(z),++x,++y,add(x,y,z),add(y,x,z);
	Ans=inf,sum=n,maxp[rt=0]=inf,getrt(1,0),sakura(rt);
	printf("%d\n",(Ans==inf)?-1:Ans);
}
