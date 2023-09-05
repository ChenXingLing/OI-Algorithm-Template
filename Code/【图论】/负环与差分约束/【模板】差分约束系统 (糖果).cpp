#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=1e5+5,M=3e5+5,inf=2e9;
int x,y,n,m,o,op,chu[N],dis[N],pan[N],head[N];long long ans;
struct QAQ{int w,to,next;}a[M];queue<int>Q;
inline void add(Re x,Re y,Re z){a[++o].to=y,a[o].w=z,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline int SPFA(Re st,Re ed){//求最小值跑最长路 
	for(Re i=0;i<=n;++i)dis[i]=-inf,chu[i]=0;
	dis[st]=0,chu[st]=pan[st]=1,Q.push(st);
	while(!Q.empty()){
		x=Q.front(),Q.pop();
		pan[x]=0;
		for(Re i=head[x],to;i;i=a[i].next)
			if(dis[to=a[i].to]<dis[x]+a[i].w){
				dis[to]=dis[x]+a[i].w;
				if((chu[to]=chu[x]+1)>n+1)return 1;
				if(!pan[to])pan[to]=1,Q.push(to);
			}
	}
	return 0;
}
int main(){
	in(n),in(m);
	for(Re i=n;i>=1;--i)add(0,i,1); //a[i]>=a[0]=1,a[i]-a[0]>=1
	while(m--){
		in(op),in(x),in(y);
		if(op<2)add(y,x,0),add(x,y,0);//a[x]==a[y]: a[x]-a[y]>=0且a[y]-a[x]>=0
		else if(op<3)add(x,y,1);//a[x]<a[y]: a[y]-a[x]>=1
		else if(op<4)add(y,x,0);//a[x]>=a[y]: a[x]-a[y]>=0
		else if(op<5)add(y,x,1);//a[x]>a[y]: a[x]-a[y]>=1
		else add(x,y,0);//a[x]<=a[y]: a[y]-a[x]>=0
		if(!(op%2)&&x==y){puts("-1");return 0;}
	}
	if(SPFA(0,n))puts("-1");
	else{
		for(Re i=1;i<=n;++i)ans+=dis[i];
		printf("%lld",ans);
	}
}
