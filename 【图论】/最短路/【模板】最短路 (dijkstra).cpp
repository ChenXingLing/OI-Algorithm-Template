#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=1e5+5,M=2e5+5,inf=2e9;
int x,y,z,n,m,o,to,st,dis[N],pan[N],head[N];
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
inline void dijkstra(Re st){
	for(Re i=0;i<=n;++i)dis[i]=inf;//��ʼ��
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
int main(){
	in(n),in(m),in(st);
	while(m--)in(x),in(y),in(z),add(x,y,z);
	dijkstra(st);
	for(Re i=1;i<=n;++i)printf("%d ",dis[i]);
}
