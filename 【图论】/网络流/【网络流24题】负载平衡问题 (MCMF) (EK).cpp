#include<algorithm>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=103,inf=2e9;
int o=1,n,h,t,S,st,ed,A[N],cyf[N],pan[N],pre[N],dis[N],head[N];LL mincost; 
struct QAQ{int w,to,next,flow;}a[N<<3];queue<int>Q;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z,Re w){a[++o].flow=z,a[o].w=w,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void add_(Re a,Re b,Re flow,Re w){add(a,b,flow,w),add(b,a,0,-w);}
inline int SPFA(Re st,Re ed){
	for(Re i=0;i<=n;++i)dis[i]=inf,pan[i]=0;
	Q.push(st),pan[st]=1,dis[st]=0,cyf[st]=inf;
	while(!Q.empty()){
		Re x=Q.front();Q.pop();pan[x]=0;
		for(Re i=head[x],to;i;i=a[i].next)
			if(a[i].flow&&dis[to=a[i].to]>dis[x]+a[i].w){
				dis[to]=dis[x]+a[i].w,pre[to]=i;
				cyf[to]=min(cyf[x],a[i].flow);
				if(!pan[to])pan[to]=1,Q.push(to);
			}
	}
	return dis[ed]!=inf;
}
inline void EK(Re st,Re ed){
	while(SPFA(st,ed)){
		Re x=ed;mincost+=(LL)cyf[ed]*dis[ed];
		while(x!=st){
			Re i=pre[x];
			a[i].flow-=cyf[ed];
			a[i^1].flow+=cyf[ed];
			x=a[i^1].to;
		}
	}
}
int main(){
	in(n);st=n+1,ed=n+2;
	for(Re i=1;i<=n;++i)in(A[i]),S+=A[i];S/=n;
	for(Re i=1;i<=n;++i){
		if(i>1)add_(i,i-1,inf,1),add_(i-1,i,inf,1);
		if(A[i]>S)add_(st,i,A[i]-S,0);
		else if(A[i]<S)add_(i,ed,S-A[i],0);
	}
	add_(1,n,inf,1),add_(n,1,inf,1);
	n+=2;EK(st,ed);
	printf("%lld",mincost);
}
