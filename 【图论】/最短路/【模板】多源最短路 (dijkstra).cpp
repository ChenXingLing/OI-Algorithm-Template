#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=105,M=4505,inf=2e9;
int x,y,z,n,m,o,to,pan[N],head[N];
struct QAQ{int w,to,next;}a[M<<1];
struct QWQ{int x,d;inline bool operator<(QWQ O)const{return d>O.d;}};//priority_queueĬ���ǴӴ�С���������������������ʱ����һ��
priority_queue<QWQ>Q;
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].to=y,a[o].w=z,a[o].next=head[x],head[x]=o;}
struct DIJKSTRA{
	int dis[N];
	inline void dijkstra(Re st){
		for(Re i=0;i<=n;++i)dis[i]=inf,pan[i]=0;//��ʼ��
		while(!Q.empty())Q.pop();
		dis[st]=0,Q.push((QWQ){st,0});//������
		while(!Q.empty()){
			x=Q.top().x,Q.pop();//ȡ��dis��С��
			if(pan[x])continue;
			pan[x]=1;//���ϱ��
			for(Re i=head[x];i;i=a[i].next)
				if(dis[to=a[i].to]>dis[x]+a[i].w){//����������
					dis[to]=dis[x]+a[i].w;
					Q.push((QWQ){to,dis[to]});//���
				}
		}
	}
}TR[N];
int main(){
	in(n),in(m);
	while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
	for(Re i=1;i<=n;++i)TR[i].dijkstra(i);
	for(Re i=1;i<=n;puts(""),++i)
		for(Re j=1;j<=n;++j)
			printf("%d ",TR[i].dis[j]);
}
