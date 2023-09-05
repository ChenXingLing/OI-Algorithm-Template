#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=4e4+3,inf=2e9;
int n,m,o,x,y,z,K,head[N];LL Ans;
struct QAQ{int w,to,next;}a[N<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int rt,sum,cnt,tmp[N],dis[N],vis[N],maxp[N],size[N];
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
	tmp[++cnt]=dis[x]=dis[fa]+w;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)getdis(to,x,a[i].w);
}
inline int calc(Re x,Re d){
	Re ans=0;cnt=0,tmp[++cnt]=dis[x]=d;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to])getdis(to,x,a[i].w);
	sort(tmp+1,tmp+cnt+1);
	Re R=cnt;
	for(Re i=1;i<=cnt&&i<R;++i){
		while(i<R&tmp[i]+tmp[R]>K)--R;
		if(i<R)ans+=(R-(i+1)+1);
	}
	return ans;
}
inline void sakura(Re x){
	Re now=sum;vis[x]=1,Ans+=calc(x,0);
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to])
			Ans-=calc(to,a[i].w),sum=size[to]>size[x]?now-size[x]:size[to],maxp[rt=0]=inf,getrt(to,x),sakura(rt);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),m=n-1;
	while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
	in(K);
	sum=n,maxp[rt=0]=inf,getrt(1,0),sakura(rt);
	printf("%lld\n",Ans);
}
