#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,inf=2e9;
int n,m,o,x,y,z,T,root,A[N],head[N];
struct QAQ{int w,to,next;}a[N<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct TREE{
	int o,head[N];
	struct QAQ{int rt,to,next;}a[N];
	inline void add(Re x,Re y,Re z){a[++o].rt=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
}T0;
int rt,sum,Sv[N],gs[N],vis[N],size[N],maxp[N],frt[N][20],fdis[N][20];LL Sdv1[N],Sdv2[N];
inline void getrt(Re x,Re fa){
	size[x]=1,maxp[x]=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)
			getrt(to,x),size[x]+=size[to],maxp[x]=max(maxp[x],size[to]);
	maxp[x]=max(maxp[x],sum-size[x]);
	if(maxp[x]<maxp[rt])rt=x;
}
inline void getdis(Re x,Re rt,Re fa,Re d){
	if(x!=rt)frt[x][++gs[x]]=rt,fdis[x][gs[x]]=d;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)getdis(to,rt,x,d+a[i].w);
}
inline void sakura(Re x){
	Re now=sum;vis[x]=1,getdis(x,x,0,0);
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to])
			sum=size[to]>size[x]?now-size[x]:size[to],maxp[rt=0]=inf,getrt(to,0),T0.add(x,to,rt),sakura(rt);
}
inline void change(Re x,Re v){
	Sdv1[x]+=v*0,Sv[x]+=v;
	for(Re i=gs[x];i>=2;--i){
		Re tmp=fdis[x][i-1];
		Sdv1[frt[x][i-1]]+=(LL)v*tmp;
		Sdv2[frt[x][i]]+=(LL)v*tmp;
		Sv[frt[x][i-1]]+=v;
	}
}
inline LL ask(Re x){
	LL ans=Sdv1[x];
	for(Re i=gs[x];i>=2;--i){
		Re tmp=fdis[x][i-1];
		ans+=Sdv1[frt[x][i-1]];
		ans-=Sdv2[frt[x][i]];
		ans+=(LL)(Sv[frt[x][i-1]]-Sv[frt[x][i]])*tmp;
	}
	return ans;
}
inline LL find(Re x){
	LL tmp=ask(x);
	for(Re i=T0.head[x];i;i=T0.a[i].next)
		if(ask(T0.a[i].to)<tmp)return find(T0.a[i].rt);
	return tmp;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),m=n-1;
	while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
	sum=n,maxp[rt=0]=inf,getrt(1,0),sakura(root=rt);
	for(Re i=1;i<=n;++i)frt[i][++gs[i]]=i;
	while(T--)in(x),in(y),change(x,y),printf("%lld\n",find(root));
}
