#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#define Re register int
using namespace std;
const int N=1e5+5,inf=2e9;
int h,t,n,p,o=1,st,ed,cnt,maxflow,Q[N],zhu[N],ans[N],pan[N],pre[N],cyf[N],head[N];
struct QAQ{int to,flow,next;}a[N<<1];vector<int>Ans[N];
inline void add(Re x,Re y,Re flow){a[++o].flow=flow,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void add_(Re x,Re y,Re flow){add(x,y,flow),add(y,x,0);}
inline int bfs(Re st,Re ed){
	for(Re i=1;i<=ed;++i)pan[i]=0;
	h=1,t=0,pan[st]=1,Q[++t]=st,cyf[st]=inf;
	while(h<=t){
		Re x=Q[h++];
		for(Re i=head[x],to;i;i=a[i].next)
			if(a[i].flow&&!pan[to=a[i].to]){
				cyf[to]=min(cyf[x],a[i].flow);
				pan[Q[++t]=to]=1,pre[to]=i;
				if(to==ed)return 1;
			}
	}
	return 0;
}
inline void EK(Re st,Re ed){
	Re x,flow=0;maxflow=0;
	while(bfs(st,ed)){
		x=ed,maxflow+=cyf[ed];
		while(x!=st){
			Re i=pre[x];
			a[i].flow-=cyf[ed];
			a[i^1].flow+=cyf[ed];
			x=a[i^1].to;
		}
	}
}
int main(){
//	freopen("123.txt","r",stdin);
	scanf("%d",&n),st=1e5+1,ed=st+1;
	while(ans[0]<=n){
		++p;
		add_(st,p<<1,1),add_(p<<1|1,ed,1);
		for(Re j=sqrt(p)+1;j*j-p<=p-1;++j)add_((j*j-p)<<1,(p<<1)|1,1);
		EK(st,ed);
		if(!maxflow)ans[++ans[0]]=p,Ans[zhu[p]=ans[0]].push_back(p);
		else{
			Re x=p<<1|1;
			while(!zhu[x-1>>1])x=a[pre[x]^1].to+1;
			Ans[zhu[x-1>>1]].push_back(p);
		}
	}
	printf("%d\n",p-1);
	for(Re i=1;i<=n;puts(""),++i)
		for(Re j=0;j<Ans[i].size();++j)
			printf("%d ",Ans[i][j]);
}
