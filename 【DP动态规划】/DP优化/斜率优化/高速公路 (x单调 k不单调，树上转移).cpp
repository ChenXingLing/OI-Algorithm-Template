#include<algorithm>
#include<cstring>
#include<cstdio>
#define LD double
#define LL long long
#define Re register int
using namespace std;
const LL N=1e6+3,inf=4e18;
int n,m,x,y,z,o,h,t,P[N],Q[N],A[N],Fa[N],head[N];LL ans,dp[N],dis[N];
struct QAQ{int w,to,next;}a[N];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
//dp[i]=min(dp[j]+P[i]*(dis[i]-dis[j])+A[i])
//dp[i]=dp[j]+P[i]*dis[i]-P[i]*dis[j]+A[i]
//P[i]*dis[j]+dp[i]-P[i]*dis[i]-A[i]=dp[j]
//  k *  x   +          b           =  y
inline LL Y(Re j){return dp[j];}
inline LL X(Re j){return dis[j];}
inline LD slope(Re i,Re j){return (LD)(Y(j)-Y(i))/(X(j)-X(i));}
inline void dfs(Re x,Re fa){
	dp[x]=inf;Re h0=h,t0=t;
	Re l=h,r=t;
	while(l<r){
		Re mid=l+r>>1;
		if(slope(Q[mid],Q[mid+1])<=P[x])l=mid+1;
		else r=mid;
	}
	h=r;
	dp[x]=dp[Q[h]]+(LL)P[x]*(dis[x]-dis[Q[h]])+A[x];
	l=h,r=t;
	while(l<r){
		Re mid=l+r+1>>1;
		if(slope(Q[mid-1],x)<=slope(Q[mid-1],Q[mid]))r=mid-1;
		else l=mid;
	}
	Re Qx0=Q[r+1];t=r,Q[++t]=x;
	for(Re i=head[x],to;i;i=a[i].next)dis[to=a[i].to]=dis[x]+a[i].w,dfs(to,x);
	h=h0,Q[t]=Qx0,t=t0;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n);
	for(Re i=2;i<=n;++i)in(x),in(z),in(P[i]),in(A[i]),add(x,i,z),Fa[i]=x;
	dp[1]=0,h=1,t=0,Q[++t]=1;
	for(Re i=head[1],to;i;i=a[i].next)
		dis[to=a[i].to]=dis[1]+a[i].w,dfs(to,1);
	for(Re i=2;i<=n;++i)printf("%lld\n",dp[i]);
}
