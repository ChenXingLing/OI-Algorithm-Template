#include<algorithm>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=11e4+5,M=6e5+5,inf=2e9;//空间：点数 N=n*n*(k+1)=110000，边数 M<=n*n*(k+1)*5+K+1（可能并不准确，因为有很多不可能出现的情况的边虽然没连，但也计算进去了） 
int x,y,z,w,o=1,n,m,h,t,A,B,C,K,st,ed,cyf[N],pan[N],pre[N],dis[N],head[N];LL mincost,maxflow; 
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
	for(Re i=0;i<=ed;++i)dis[i]=inf,pan[i]=0;
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
		Re x=ed;maxflow+=cyf[ed],mincost+=(LL)cyf[ed]*dis[ed];
		while(x!=st){
			Re i=pre[x];
			a[i].flow-=cyf[ed];
			a[i^1].flow+=cyf[ed];
			x=a[i^1].to;
		}
	}
}
inline int P(Re x,Re y,Re k){return (x-1)*n+y+k*n*n;}
int main(){
	in(n),in(K),in(A),in(B),in(C),st=(K+1)*n*n+1,ed=st+1;//一共有(K+1)层 
	add_(st,P(1,1,0),1,0);//超级源点连到满油的(1,1) 
	for(Re k=1;k<=K;++k)add_(P(n,n,k),ed,1,0);
//把每一层的(n,n)连到超级汇点，由于n>=2，所以起点不可能等于终点，因此不可能满油到终点，所以第0层不连 
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=n;++j){
			in(x);
			if(x){//已有加油站 
				for(Re k=1;k<=K;++k)add_(P(i,j,k),P(i,j,0),inf,A);
				//所有状态都必须花费A加油加到满，但由于不可能满油到达某一点，所以满油的第0层可以不加（连） 
				//加满油之后状态可以由满油状态到达K-1油的上下左右四个方向 
				if(i<n)add_(P(i,j,0),P(i+1,j,1),inf,0);//横坐标+1,费用为0 
				if(j<n)add_(P(i,j,0),P(i,j+1,1),inf,0);//纵坐标+1,费用为0 
				if(i>1)add_(P(i,j,0),P(i-1,j,1),inf,B);//横坐标-1,费用为B 
				if(j>1)add_(P(i,j,0),P(i,j-1,1),inf,B);//纵坐标-1,费用为B 
			}
			else{//无加油站 
				for(Re k=0;k<K;++k){//从有油的状态到达四个方向 
					if(i<n)add_(P(i,j,k),P(i+1,j,k+1),inf,0);//横坐标+1,费用为0 
					if(j<n)add_(P(i,j,k),P(i,j+1,k+1),inf,0);//纵坐标+1,费用为0 
					if(i>1)add_(P(i,j,k),P(i-1,j,k+1),inf,B);//横坐标-1,费用为B 
					if(j>1)add_(P(i,j,k),P(i,j-1,k+1),inf,B);//纵坐标-1,费用为B 
				}
				add_(P(i,j,K),P(i,j,0),1,A+C);//没有加油站的地方可以自给自足 
			}
		}
	EK(st,ed);//跑一跑模板MCMF 
	printf("%lld",mincost);
}
