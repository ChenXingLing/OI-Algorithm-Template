#include<algorithm>
#include<iostream>
#include<string>
#include<cstdio>
#include<queue>
#include<map>
#define LL long long
#define Re register int
using namespace std;
const int N=103,M=40000,inf=2e9;
int x,y,o=1,n,m,h,t,st,ed,flag,cyf[N],pan[N],pre[N],dis[N],head[N];LL maxcost,maxflow;
struct QAQ{int w,to,next,flow;}a[M<<1];queue<int>Q;string CH,ch[N];map<string,int>ip;
inline void add(Re x,Re y,Re z,Re w){a[++o].flow=z,a[o].w=w,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void add_(Re a,Re b,Re flow,Re w){add(a,b,flow,w),add(b,a,0,-w);}
inline int SPFA(Re st,Re ed){
	for(Re i=0;i<=ed;++i)dis[i]=-inf,pan[i]=0;
	Q.push(st),pan[st]=1,dis[st]=0,cyf[st]=inf;
	while(!Q.empty()){
		Re x=Q.front();Q.pop();pan[x]=0;
		for(Re i=head[x],to;i;i=a[i].next)
			if(a[i].flow&&dis[to=a[i].to]<dis[x]+a[i].w){//�· 
				dis[to]=dis[x]+a[i].w,pre[to]=i;
				cyf[to]=min(cyf[x],a[i].flow);//��С�������� 
				if(!pan[to])pan[to]=1,Q.push(to);
			}
	}
	return dis[ed]!=-inf;
}
inline void EK(Re st,Re ed){
	while(SPFA(st,ed)){
		Re x=ed;maxflow+=cyf[ed],maxcost+=(LL)cyf[ed]*dis[ed];
		while(x!=st){
			Re i=pre[x];
			a[i].flow-=cyf[ed];
			a[i^1].flow+=cyf[ed];
			x=a[i^1].to;
		}
	}
}
inline void dfs1(Re x){
	pan[x]=1;//��¼һ�µ�һ��ѡ�ĵ㣬�ڶ��ξͲ�ѡ������ 
	cout<<ch[x-n]<<endl;//��һ������������ǵü�n 
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)<=n&&!a[i].flow){dfs1(to+n);break;}//����x>n�����to<=n,�ٴ�to�ĳ�������ȥ 
}
inline void dfs2(Re x){
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)<=n&&!a[i].flow&&!pan[to+n])dfs2(to+n);//����x>n�����to<=n,�ٴ�to�ĳ�������ȥ 
	cout<<ch[x-n]<<endl;//�ڶ��ε���������ǵü�n 
}
int main(){
	cin>>n>>m;st=1,ed=n<<1;
	for(Re i=1;i<=n;++i)cin>>ch[i],ip[ch[i]]=i;
	for(Re i=2;i<n;++i)add_(i,n+i,1,1);//1~n��ʾ��㣬n+1~2n��ʾ���� 
	add_(1,1+n,2,1),add_(n,n+n,2,1);//�����е���Ծ������� 
	while(m--){
		cin>>CH;x=ip[CH];
		cin>>CH;y=ip[CH];
		if(x>y)swap(x,y);
		flag|=x==1&&y==n; 
		add_(x+n,y,1,0);//�մ�x�ĳ������������������y����� 
	}
	EK(st,ed);
	if(maxflow==2)printf("%d\n",maxcost-2);//�ҵ�������· 
	else if(maxflow==1&&flag){//ֻ��һ����1ֱͨn�ı� 
		printf("2\n");
		cout<<ch[1]<<endl<<ch[n]<<endl<<ch[1]<<endl;//����Ҫ������� 
		return 0;
	}
	else return !printf("No Solution!\n");
	for(Re i=1;i<=n+2;++i)pan[i+n]=0;
	dfs1(1+n),dfs2(1+n);//���ݱߵĲ����������ж��Ƿ�ѡ�˸ñߣ����Դӳ��㿪ʼ�ѣ����ﺦ�ҵ���һ����Сʱ 
}
