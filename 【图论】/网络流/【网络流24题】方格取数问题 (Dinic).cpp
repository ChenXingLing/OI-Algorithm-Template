#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=1e4+5,M=3e4+5,inf=2e9;
int x,n,m,h,t,o=1,T,st,ed,ans,maxflow,Q[N],cur[N],dis[N],head[N],wi[4]={0,0,1,-1},wj[4]={1,-1,0,0};
struct QAQ{int to,next,flow;}a[M<<1];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].flow=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void add_(Re x,Re y,Re z){add(x,y,z),add(y,x,0);}
inline int bfs(Re st,Re ed){//bfs求源点到所有点的最短路 
    for(Re i=0;i<=ed;++i)cur[i]=head[i],dis[i]=0;//当前弧优化cur=head
    h=1,t=0,dis[st]=1,Q[++t]=st;
    while(h<=t){
        Re x=Q[h++],to;
        for(Re i=head[x];i;i=a[i].next)
            if(a[i].flow&&!dis[to=a[i].to]){
            	dis[to]=dis[x]+1,Q[++t]=to;
            	if(to==ed)return 1;
            }
    }
    return 0;
}
inline int dfs(Re x,Re flow){//flow为源点到x的路径上的最小边权 
    if(!flow||x==ed)return flow;//发现没有流了或者到达终点即可返回 
    Re tmp=0,to,f;
    for(Re i=cur[x];i;i=a[i].next){
    	cur[x]=i;//当前弧优化cur=i
    	if(dis[to=a[i].to]==dis[x]+1&&(f=dfs(to,min(flow-tmp,a[i].flow)))){
    	//若边权为0，不满足增广路性质，此时dfs返回值f为0，不必执行下面了 
            a[i].flow-=f,a[i^1].flow+=f;
            tmp+=f;//记录终点已经有了多少流 
            if(!(flow-tmp))break;//前面那些儿子都是最短路，这些最优路径已经榨干了从x出来的所有流，后面的都不用管了 
    	}
    }
    return tmp;
}
inline void Dinic(Re st,Re ed){
    Re flow=0;maxflow=0;
    while(bfs(st,ed))maxflow+=dfs(st,inf);
}
inline int Poi(Re i,Re j){return (i-1)*m+j;}
int main(){
	in(n),in(m),st=n*m+1,ed=st+1;
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=m;++j){
			in(x),ans+=x;
			if((i+j)%2)add_(st,Poi(i,j),x);
			else add_(Poi(i,j),ed,x);
		}
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=m;++j)
			if((i+j)%2)for(Re k=0;k<4;++k){
				Re ni=i+wi[k],nj=j+wj[k];
				if(ni>=1&&ni<=n&&nj>=1&&nj<=m)add_(Poi(i,j),Poi(ni,nj),inf);
			}
	Dinic(st,ed);
	printf("%d\n",ans-maxflow);
}