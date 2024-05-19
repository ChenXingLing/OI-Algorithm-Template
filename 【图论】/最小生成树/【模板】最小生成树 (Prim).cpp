#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=5003,M=2e5+3,inf=2e9;
int x,y,z,n,m,o,ans,pan[N],dis[N],head[N];
struct QAQ{int w,to,next;}a[M<<1];
struct QWQ{int x,d;inline bool operator<(QWQ o)const{return d>o.d;};};
priority_queue<QWQ>Q;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void Prim(){
	for(Re i=0;i<=n;++i)pan[i]=0,dis[i]=inf;
	Re t=0;Q.push((QWQ){1,dis[1]=0});
	while(!Q.empty()&t<n){
		Re x=Q.top().x;Q.pop();
		if(pan[x])continue;
		pan[x]=1,++t,ans+=dis[x];
		for(Re i=head[x],to;i;i=a[i].next)
			if(dis[to=a[i].to]>a[i].w)Q.push((QWQ){to,dis[to]=a[i].w});
	}
}
int main(){
	in(n),in(m);
	while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
	Prim();
	printf("%d",ans);
}
