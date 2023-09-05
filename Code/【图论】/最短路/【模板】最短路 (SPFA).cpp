#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=1e4+5,M=5e5+5,inf=2147483647;
int x,y,z,n,m,o,to,st,dis[N],pan[N],head[N];
struct QAQ{int w,to,next;}a[M<<1];
queue<int>Q;
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].to=y,a[o].w=z,a[o].next=head[x],head[x]=o;}
inline void SPFA(Re st){
	for(Re i=0;i<=n;++i)dis[i]=inf;
	dis[st]=0,pan[st]=1,Q.push(st);
	while(!Q.empty()){
		x=Q.front(),Q.pop();
		pan[x]=0;
		for(Re i=head[x];i;i=a[i].next)
			if(dis[to=a[i].to]>dis[x]+a[i].w){
				dis[to]=dis[x]+a[i].w;
				if(!pan[to])pan[to]=1,Q.push(to);
			}
	}
}
int main(){
	in(n),in(m),in(st);
	while(m--)in(x),in(y),in(z),add(x,y,z);
	SPFA(st);
	for(Re i=1;i<=n;++i)printf("%d ",dis[i]);
}
