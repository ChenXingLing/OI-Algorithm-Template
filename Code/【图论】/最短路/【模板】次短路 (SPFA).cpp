#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=5003,M=1e5+3,inf=1e9;
int n,m,x,y,z,o,pan[N],head[N],dis[N][2];
struct QAQ{int w,to,next;}a[M<<1];queue<int>Q;
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    Re fu=0;x=0;char ch=getchar();
    while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=fu?-x:x;
}
inline void SPFA(Re st){
	for(Re i=1;i<=n;++i)dis[i][0]=dis[i][1]=inf;
	Q.push(st),dis[st][0]=0,pan[st]=1;
	while(!Q.empty()){
		Re x=Q.front();Q.pop();pan[x]=0;
		for(Re i=head[x],to;i;i=a[i].next){
//��x�ڵ��ȥ��������Ϣ�����dis[x][0]+a[i].w�ʹζ�dis[x][1]+a[i].w���ֱ�������������ȥ����dis[to]����̺ʹζ� 
			if(dis[to=a[i].to][0]>dis[x][0]+a[i].w){//x���+w ����to��� 
				dis[to][1]=dis[to][0];//�Ȱ�to����̴����ζ�
				dis[to][0]=dis[x][0]+a[i].w;
				if(!pan[to])pan[to]=1,Q.push(to);
			}
			if(dis[to][0]<dis[x][0]+a[i].w&&dis[to][1]>dis[x][0]+a[i].w){//x���+w ����to��̣�������to�ζ�
			//��ע�����ﲻ�ܽ����������Ǹ�ifдһ��else����Ϊ��dis[to][0]==dis[x][0]+a[i].wʱ�ǲ��ܸ���to�ζ̵ģ�����to����̺ʹζ̾�һ�����ˣ� 
				dis[to][1]=dis[x][0]+a[i].w;
				if(!pan[to])pan[to]=1,Q.push(to);
			}
			if(dis[to][1]>dis[x][1]+a[i].w){//x�ζ�+w ����to�ζ̣�x�ζ�+w �ǲ����ܸ���to��̵ģ���Ϊǰ���Ѿ���һ���������"x���+w"�ˣ� 
				dis[to][1]=dis[x][1]+a[i].w;
				if(!pan[to])pan[to]=1,Q.push(to);
			}
		}
	}
}
int main(){
    in(n),in(m);
    while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
    SPFA(1);
    printf("%d\n",dis[n][1]);
}
