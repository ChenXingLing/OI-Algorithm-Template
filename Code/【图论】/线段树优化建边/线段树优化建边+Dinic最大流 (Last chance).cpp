#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=5003+3,M=25e4+3,inf=2e9;
int n,m,x,y,z,O,op,st,ed,X[N],Y[N],Z[N],Ans[N],cnt[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Network_Flow{
	int o,h,t,maxflow,Q[N*3],dis[N*3],cur[N*3],head[N*3];
	struct QAQ{int to,next,flow;}a[M<<1];
	inline void add_(Re x,Re y,Re flow){a[++o].to=y,a[o].flow=flow,a[o].next=head[x],head[x]=o;}
	inline void add(Re x,Re y,Re flow){add_(x,y,flow),add_(y,x,0);}
	inline int bfs(Re st,Re ed){
		for(Re i=0;i<=ed;++i)dis[i]=0,cur[i]=head[i];
		h=1,t=0,dis[Q[++t]=st]=1;
		while(h<=t){
			Re x=Q[h++];
			for(Re i=head[x],to;i;i=a[i].next)
				if(a[i].flow&&!dis[to=a[i].to]){
					dis[Q[++t]=to]=dis[x]+1;
					if(to==ed)return 1;
				}
		}
		return 0;
	}
	inline int dfs(Re x,Re flow){
		if(x==ed||!flow)return flow;
		Re tmp=0,to,f;
		for(Re i=cur[x];i;i=a[i].next){
			cur[x]=i;
			if(dis[to=a[i].to]==dis[x]+1&&(f=dfs(to,min(a[i].flow,flow-tmp)))){
				a[i].flow-=f,a[i^1].flow+=f,tmp+=f;
				if(tmp==flow)break;
			}
		}
		return tmp;
	}
	inline void dinic(Re st,Re ed){while(bfs(st,ed))maxflow+=dfs(st,inf);}
	inline int find(Re x){
		Re last=ed;
		while(x<=O||x>O+n){
			for(Re i=head[x];i;i=a[i].next)
				if(a[i^1].to==x&&a[i].to!=last&&a[i].flow){//由于本题的特殊性，此处的a[i^1].to==x可以省略
					--a[i].flow,last=x,x=a[i].to;break;
				}
		}
		return x-O;
	}
}T1;
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	struct QAQ{int in;}tr[N<<2];
	inline void build(Re p,Re L,Re R){
		if(L==R){tr[p].in=L;return;}
		tr[p].in=++O,build(pl,L,mid),build(pr,mid+1,R);
		T1.add(tr[p].in,tr[pl].in,inf),T1.add(tr[p].in,tr[pr].in,inf);
	}
	inline void change(Re p,Re L,Re R,Re l,Re r,Re x,Re w){
		if(l<=L&&R<=r){T1.add(x,tr[p].in,w);return;}
		if(l<=mid)change(pl,L,mid,l,r,x,w);
		if(r>mid)change(pr,mid+1,R,l,r,x,w);
	}
}TR;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),T1.o=1,O=m,TR.build(1,1,m),st=O+n+1,ed=st+1;
	for(Re i=1;i<=n;++i){
		in(op);
		if(op<1){
			in(x),T1.add(st,O+i,1);
			while(x--)in(y),T1.add(O+i,y,1);
		}
		else if(op<2)in(x),in(y),T1.add(st,O+i,1),TR.change(1,1,m,x,y,O+i,1);
		else{
			in(x),in(y),in(z),T1.add(st,O+i,2),X[i]=x,Y[i]=y,Z[i]=z;
			T1.add(O+i,x,1),T1.add(O+i,y,1),T1.add(O+i,z,1);
		}
	}
	for(Re j=1;j<=m;++j)T1.add(j,ed,1);
	T1.dinic(st,ed),printf("%d\n",T1.maxflow);
	for(Re i=T1.head[ed];i;i=T1.a[i].next)
		if(T1.a[i].flow)++cnt[Ans[T1.a[i].to]=T1.find(T1.a[i].to)];
	for(Re i=1;i<=n;++i)
		if(X[i]&&cnt[i]==1){
			if(Ans[X[i]]==i)Ans[Y[i]]=i;
			else Ans[X[i]]=i;
		}
	for(Re i=1;i<=m;++i)if(Ans[i])printf("%d %d\n",Ans[i],i);
}
