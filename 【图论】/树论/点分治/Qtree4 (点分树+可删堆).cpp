#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,logN=18,inf=1e9;
int n,m,x,y,z,o,T,Cnt,A[N],ans[N],head[N];char op;
struct QAQ{int w,to,next;}a[N<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct LCA{
	int O,lg[N<<1],fir[N],idx[N<<1],idd[N<<1],dis[N],deep[N],f[N<<1][20],ans[N<<1][20];
	inline void dfs(Re x,Re fa,Re w){
		idx[fir[x]=++O]=x,idd[O]=deep[x]=deep[fa]+1,dis[x]=dis[fa]+w;
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=fa)dfs(to,x,a[i].w),idx[++O]=x,idd[O]=deep[x];
	}
	inline void build(Re rt){
		dfs(rt,0,0),lg[0]=-1;
		for(Re i=1;i<=O;++i)f[i][0]=idd[i],ans[i][0]=idx[i],lg[i]=lg[i>>1]+1;
		for(Re j=1;j<=logN;++j)
			for(Re i=1;i+(1<<j)-1<=O;++i)
				if(f[i][j-1]<f[i+(1<<j-1)][j-1])f[i][j]=f[i][j-1],ans[i][j]=ans[i][j-1];
				else f[i][j]=f[i+(1<<j-1)][j-1],ans[i][j]=ans[i+(1<<j-1)][j-1];
	}
	inline int lca(Re x,Re y){
		Re L=fir[x],R=fir[y];
		if(L>R)swap(L,R);
		Re m=lg[R-L+1];
		return f[L][m]<f[R-(1<<m)+1][m]?ans[L][m]:ans[R-(1<<m)+1][m];
	}
}T0;
inline int Dis(Re x,Re y){return T0.dis[x]+T0.dis[y]-(T0.dis[T0.lca(x,y)]<<1);}
struct Queue{
	priority_queue<int>Q,D;
	inline int top(){
		while(!Q.empty()&&!D.empty()&&Q.top()==D.top())Q.pop(),D.pop();
		return Q.empty()?-inf:Q.top();
	}
	inline int sec(){
		Re x=top();if(x==-inf)return x;
		Q.pop();Re ans=top();Q.push(x);
		return ans;
	}
	inline void erase(Re x){if(Q.top()==x)Q.pop();else D.push(x);}
	inline void insert(Re x){Q.push(x);}
	inline int empty(){
		while(!Q.empty()&&!D.empty()&&Q.top()==D.top())Q.pop(),D.pop();
		return Q.empty();
	}
}Ans,Q[N],dis[N];
int rt,sum,Fa[N],vis[N],size[N],maxp[N];
inline void getrt(Re x,Re fa){
	size[x]=1,maxp[x]=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)
			getrt(to,x),size[x]+=size[to],maxp[x]=max(maxp[x],size[to]);
	maxp[x]=max(maxp[x],sum-size[x]);
	if(maxp[x]<maxp[rt])rt=x;
}
inline void getdis(Re x,Re fa,Re rt){
	dis[rt].insert(Dis(x,Fa[rt]));
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)getdis(to,x,rt);
}
inline void sakura(Re x){
	Re now=sum;vis[x]=1,getdis(x,0,x);
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]){
			sum=size[to]>size[x]?now-size[x]:size[to],maxp[rt=0]=inf,getrt(to,0);
			Fa[to=rt]=x,sakura(rt),Q[x].insert(dis[to].top());
		}
	Q[x].insert(0),Ans.insert(ans[x]=max(0,Q[x].top()+Q[x].sec()));
}
inline void insert(Re x){
	Ans.erase(ans[x]),Q[x].insert(0),Ans.insert(ans[x]=max(0,Q[x].top()+Q[x].sec()));
	for(Re fa=x;Fa[fa];fa=Fa[fa]){
		Re pa=Fa[fa];
		Ans.erase(ans[pa]);
		if(!dis[fa].empty())Q[pa].erase(dis[fa].top());
		
		dis[fa].insert(Dis(x,pa));
		
		Q[pa].insert(dis[fa].top());
		Ans.insert(ans[pa]=max(0,Q[pa].top()+Q[pa].sec()));
	}
}
inline void erase(Re x){
	Ans.erase(ans[x]),Q[x].erase(0),Ans.insert(ans[x]=max(0,Q[x].top()+Q[x].sec()));
	for(Re fa=x;Fa[fa];fa=Fa[fa]){
		Re pa=Fa[fa];
		Ans.erase(ans[pa]);
		Q[pa].erase(dis[fa].top());
		
		dis[fa].erase(Dis(x,pa));
		
		if(!dis[fa].empty())Q[pa].insert(dis[fa].top());
		Ans.insert(ans[pa]=max(0,Q[pa].top()+Q[pa].sec()));
	}
}
inline void change(Re x){
	if(A[x])insert(x),A[x]=0,++Cnt;
	else erase(x),A[x]=1,--Cnt;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),m=n-1,Cnt=n;
	while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
	in(T),T0.build(1),sum=n,maxp[rt=0]=inf,getrt(1,0),sakura(rt);
	while(T--){
		scanf(" %c",&op);
		if(op=='C')in(x),change(x);
		else if(!Cnt)puts("They have disappeared.");
		else printf("%d\n",Cnt<2?0:Ans.top());
	}
}
