#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=3003,M=6003,inf=1e9;
int x,y,z,n,m,o,to,dis[N],cnt[N],pan[N],head[N];queue<int>Q;
struct TAT{int x,y,z;}A[M];
struct QAQ{int to,next,w;}a[N+M];
inline void add(Re x,Re y,Re z){a[++o].to=y,a[o].w=z,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline int SPFA(Re st,Re n){
	for(Re i=0;i<=n;++i)dis[i]=inf;
	dis[st]=0,pan[st]=cnt[st]=1,Q.push(st);
	while(!Q.empty()){
		x=Q.front(),Q.pop();
		pan[x]=0;
		for(Re i=head[x];i;i=a[i].next)
			if(dis[to=a[i].to]>dis[x]+a[i].w){
				dis[to]=dis[x]+a[i].w;
				if((cnt[to]=cnt[x]+1)>n)return 1;
				if(!pan[to])pan[to]=1,Q.push(to);
			}
	}
	return 0;
}
struct DIJKSTRA{
	int o,head[N],dis[N];QAQ a[M];
	struct QWQ{int x,d;inline bool operator<(QWQ O)const{return d>O.d;}};//priority_queue默认是从大到小排序，所以这里重载运算符时方向反一下
	priority_queue<QWQ>Q;
	inline void add(Re x,Re y,Re z){a[++o].to=y,a[o].w=z,a[o].next=head[x],head[x]=o;}
	inline void dijkstra(Re st){
		for(Re i=0;i<=n;++i)dis[i]=inf,pan[i]=0;//初始化
		while(!Q.empty())Q.pop();
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
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m);
	for(int i=1;i<=m;++i)in(x),in(y),in(z),add(A[i].x=x,A[i].y=y,A[i].z=z);
	for(int i=1;i<=n;++i)add(0,i,0);
	if(SPFA(0,n+1))return !puts("-1");//n+1个点 
	for(int i=1;i<=m;++i)T1.add(A[i].x,A[i].y,A[i].z+dis[A[i].x]-dis[A[i].y]);
	for(Re i=1;i<=n;++i){
		T1.dijkstra(i);LL ans=0;
		for(Re j=1;j<=n;++j)
			if(T1.dis[j]==inf)ans+=(LL)j*inf;
			else ans+=(LL)j*(T1.dis[j]-dis[i]+dis[j]);
		printf("%lld\n",ans);
	}
}
