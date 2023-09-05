#include<algorithm>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=11e4+5,M=6e5+5,inf=2e9;//�ռ䣺���� N=n*n*(k+1)=110000������ M<=n*n*(k+1)*5+K+1�����ܲ���׼ȷ����Ϊ�кܶ಻���ܳ��ֵ�����ı���Ȼû������Ҳ�����ȥ�ˣ� 
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
	in(n),in(K),in(A),in(B),in(C),st=(K+1)*n*n+1,ed=st+1;//һ����(K+1)�� 
	add_(st,P(1,1,0),1,0);//����Դ���������͵�(1,1) 
	for(Re k=1;k<=K;++k)add_(P(n,n,k),ed,1,0);
//��ÿһ���(n,n)����������㣬����n>=2��������㲻���ܵ����յ㣬��˲��������͵��յ㣬���Ե�0�㲻�� 
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=n;++j){
			in(x);
			if(x){//���м���վ 
				for(Re k=1;k<=K;++k)add_(P(i,j,k),P(i,j,0),inf,A);
				//����״̬�����뻨��A���ͼӵ����������ڲ��������͵���ĳһ�㣬�������͵ĵ�0����Բ��ӣ����� 
				//������֮��״̬����������״̬����K-1�͵����������ĸ����� 
				if(i<n)add_(P(i,j,0),P(i+1,j,1),inf,0);//������+1,����Ϊ0 
				if(j<n)add_(P(i,j,0),P(i,j+1,1),inf,0);//������+1,����Ϊ0 
				if(i>1)add_(P(i,j,0),P(i-1,j,1),inf,B);//������-1,����ΪB 
				if(j>1)add_(P(i,j,0),P(i,j-1,1),inf,B);//������-1,����ΪB 
			}
			else{//�޼���վ 
				for(Re k=0;k<K;++k){//�����͵�״̬�����ĸ����� 
					if(i<n)add_(P(i,j,k),P(i+1,j,k+1),inf,0);//������+1,����Ϊ0 
					if(j<n)add_(P(i,j,k),P(i,j+1,k+1),inf,0);//������+1,����Ϊ0 
					if(i>1)add_(P(i,j,k),P(i-1,j,k+1),inf,B);//������-1,����ΪB 
					if(j>1)add_(P(i,j,k),P(i,j-1,k+1),inf,B);//������-1,����ΪB 
				}
				add_(P(i,j,K),P(i,j,0),1,A+C);//û�м���վ�ĵط������Ը����� 
			}
		}
	EK(st,ed);//��һ��ģ��MCMF 
	printf("%lld",mincost);
}
