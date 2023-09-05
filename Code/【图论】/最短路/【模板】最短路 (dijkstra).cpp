#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=1e5+5,M=2e5+5,inf=2e9;
int x,y,z,n,m,o,to,st,dis[N],pan[N],head[N];
struct QAQ{int w,to,next;}a[M<<1];
struct QWQ{int x,d;inline bool operator<(QWQ O)const{return d>O.d;}};//priority_queue默认是从大到小排序，所以这里重载运算符时方向反一下
priority_queue<QWQ>Q;
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].to=y,a[o].w=z,a[o].next=head[x],head[x]=o;}
inline void dijkstra(Re st){
	for(Re i=0;i<=n;++i)dis[i]=inf;//初始化
	dis[st]=0,Q.push((QWQ){st,0});//起点入队
	while(!Q.empty()){
		x=Q.top().x,Q.pop();//取出dis最小者
		if(pan[x])continue;
		pan[x]=1;//打上标记
		for(Re i=head[x];i;i=a[i].next)
			if(dis[to=a[i].to]>dis[x]+a[i].w){//更新其他点
				dis[to]=dis[x]+a[i].w;
				Q.push((QWQ){to,dis[to]});//入队
			}
	}
}
int main(){
	in(n),in(m),in(st);
	while(m--)in(x),in(y),in(z),add(x,y,z);
	dijkstra(st);
	for(Re i=1;i<=n;++i)printf("%d ",dis[i]);
}
