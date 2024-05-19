#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=1200,M=1865,inf=2e9;//点数：(2m+n-1)*n/2*2+2=(3n-1)*n+2=1182 边数：1.5*n*n*3+m+m+n-1=4.5*n*n+3n=1860
int o=1,n,m,h,t,st,ed,O,Poi[23][43],A[23][43],cyf[N],pan[N],pre[N],dis[N],head[N];LL maxcost,maxflow; 
struct QAQ{int w,to,next,flow;}a[M<<1];queue<int>Q;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z,Re w){a[++o].flow=z,a[o].w=w,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void add_(Re a,Re b,Re flow,Re w){add(a,b,flow,w),add(b,a,0,-w);}
inline int SPFA(Re st,Re ed){
    for(Re i=0;i<=ed;++i)dis[i]=-inf,pan[i]=0;
    Q.push(st),pan[st]=1,dis[st]=0,cyf[st]=inf;
    while(!Q.empty()){
    	Re x=Q.front();Q.pop();pan[x]=0;
    	for(Re i=head[x],to;i;i=a[i].next)
    		if(a[i].flow&&dis[to=a[i].to]<dis[x]+a[i].w){//求最大花费
    			dis[to]=dis[x]+a[i].w,pre[to]=i;
    			cyf[to]=min(cyf[x],a[i].flow);
    			if(!pan[to])pan[to]=1,Q.push(to);
    		}
    }
    return dis[ed]!=-inf;
}
inline void EK(Re st,Re ed){
    while(SPFA(st,ed)){
    	Re x=ed;maxflow+=cyf[ed],maxcost+=(LL)cyf[ed]*dis[ed];
    	while(x!=st){
    		Re i=pre[x];
    		a[i].flow-=cyf[ed];
    		a[i^1].flow+=cyf[ed];
    		x=a[i^1].to;
    	}
    }
}
inline void TAT1(){
    for(Re i=1;i<=m;++i)add_(st,Poi[1][i],1,0);
    for(Re i=1;i<=m+n-1;++i)add_(Poi[n][i]+O,ed,1,0);
    for(Re i=1;i<=n;++i)
    	for(Re j=1;j<=m+i-1;++j){
    		add_(Poi[i][j],Poi[i][j]+O,1,A[i][j]);
    		if(i<n)add_(Poi[i][j]+O,Poi[i+1][j],1,0),add_(Poi[i][j]+O,Poi[i+1][j+1],1,0);
    	}
    EK(st,ed);
    printf("%lld\n",maxcost);
}
inline void TAT2(){
    for(Re i=1;i<=m;++i)add_(st,Poi[1][i],1,0);
    for(Re i=1;i<=m+n-1;++i)add_(Poi[n][i]+O,ed,inf,0);
    for(Re i=1;i<=n;++i)
    	for(Re j=1;j<=m+i-1;++j){
    		add_(Poi[i][j],Poi[i][j]+O,inf,A[i][j]);
    		if(i<n)add_(Poi[i][j]+O,Poi[i+1][j],1,0),add_(Poi[i][j]+O,Poi[i+1][j+1],1,0);
    	}
    EK(st,ed);
    printf("%lld\n",maxcost);
}
inline void TAT3(){
    for(Re i=1;i<=m;++i)add_(st,Poi[1][i],1,0);
    for(Re i=1;i<=m+n-1;++i)add_(Poi[n][i]+O,ed,inf,0);
    for(Re i=1;i<=n;++i)
    	for(Re j=1;j<=m+i-1;++j){
            add_(Poi[i][j],Poi[i][j]+O,inf,A[i][j]);
            if(i<n)add_(Poi[i][j]+O,Poi[i+1][j],inf,0),add_(Poi[i][j]+O,Poi[i+1][j+1],inf,0);
    	}
    EK(st,ed);
    printf("%lld\n",maxcost);
}
inline void CL(){
    memset(head,0,sizeof(head));
    memset(cyf,0,sizeof(cyf));
    memset(pre,0,sizeof(pre));
    memset(a,0,sizeof(a));
    maxflow=maxcost=0,o=1;
}
int main(){
    in(m),in(n);
    for(Re i=1;i<=n;++i)
    	for(Re j=1;j<=m+i-1;++j)
            in(A[i][j]),Poi[i][j]=++O;
    st=O<<1|1,ed=st+1;
    TAT1(),CL(),TAT2(),CL(),TAT3();
}
