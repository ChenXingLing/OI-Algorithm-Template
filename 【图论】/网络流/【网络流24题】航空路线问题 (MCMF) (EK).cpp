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
			if(a[i].flow&&dis[to=a[i].to]<dis[x]+a[i].w){//最长路 
				dis[to]=dis[x]+a[i].w,pre[to]=i;
				cyf[to]=min(cyf[x],a[i].flow);//最小残余网络 
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
	pan[x]=1;//记录一下第一次选的点，第二次就不选它们了 
	cout<<ch[x-n]<<endl;//第一次正序输出。记得减n 
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)<=n&&!a[i].flow){dfs1(to+n);break;}//出点x>n到入点to<=n,再从to的出点搜下去 
}
inline void dfs2(Re x){
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)<=n&&!a[i].flow&&!pan[to+n])dfs2(to+n);//出点x>n到入点to<=n,再从to的出点搜下去 
	cout<<ch[x-n]<<endl;//第二次倒序输出。记得减n 
}
int main(){
	cin>>n>>m;st=1,ed=n<<1;
	for(Re i=1;i<=n;++i)cin>>ch[i],ip[ch[i]]=i;
	for(Re i=2;i<n;++i)add_(i,n+i,1,1);//1~n表示入点，n+1~2n表示出点 
	add_(1,1+n,2,1),add_(n,n+n,2,1);//起点和中点可以经过两次 
	while(m--){
		cin>>CH;x=ip[CH];
		cin>>CH;y=ip[CH];
		if(x>y)swap(x,y);
		flag|=x==1&&y==n; 
		add_(x+n,y,1,0);//刚从x的出点出来，接下来连到y的入点 
	}
	EK(st,ed);
	if(maxflow==2)printf("%d\n",maxcost-2);//找到了两条路 
	else if(maxflow==1&&flag){//只有一条从1直通n的边 
		printf("2\n");
		cout<<ch[1]<<endl<<ch[n]<<endl<<ch[1]<<endl;//这里要输出三个 
		return 0;
	}
	else return !printf("No Solution!\n");
	for(Re i=1;i<=n+2;++i)pan[i+n]=0;
	dfs1(1+n),dfs2(1+n);//根据边的残余网络来判断是否选了该边，所以从出点开始搜，这里害我调了一个多小时 
}
