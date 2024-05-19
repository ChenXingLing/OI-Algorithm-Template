#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
const LL inf=1e18;
int n,m,x,y,w,l,r,o,op,st,head[N<<3];bool pan[N<<3];LL dis[N<<3];
struct QAQ{int w,to,next;}a[(N<<3)+(N<<2)+N*18*2];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	int O;
	struct QAQ{int in,out;}tr[N<<2];
	inline void build(Re p,Re L,Re R){
		if(L==R){tr[p].in=tr[p].out=L;return;}
		tr[p].in=++O,tr[p].out=++O,add(tr[p].in,tr[p].out,0);
		build(pl,L,mid),build(pr,mid+1,R);
		add(tr[p].in,tr[pl].in,0),add(tr[p].in,tr[pr].in,0);
		add(tr[pl].out,tr[p].out,0),add(tr[pr].out,tr[p].out,0);
	}
	inline void change(Re p,Re L,Re R,Re l,Re r,Re x,Re w,Re op){
		if(l<=L&&R<=r){
			if(op)add(tr[p].out,x,w);
			else add(x,tr[p].in,w);
			return;
		}
		if(l<=mid)change(pl,L,mid,l,r,x,w,op);
		if(r>mid)change(pr,mid+1,R,l,r,x,w,op);
	}
}TR;
struct QWQ{int x;LL d;inline bool operator<(const QWQ &O)const{return d>O.d;}};
priority_queue<QWQ>Q;
inline void dijkstra(Re st){
	for(Re i=1;i<=TR.O;++i)dis[i]=inf;
	Q.push((QWQ){st,dis[st]=0});
	while(!Q.empty()){
		Re x=Q.top().x;Q.pop();
		if(pan[x])continue;
		pan[x]=0;
		for(Re i=head[x],to;i;i=a[i].next)
			if(dis[to=a[i].to]>dis[x]+a[i].w)
				Q.push((QWQ){to,dis[to]=dis[x]+a[i].w});
	}
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),in(st);
	TR.O=n,TR.build(1,1,n);
	while(m--){
		in(op),in(x);
		if(op<2)in(y),in(w),TR.change(1,1,n,y,y,x,w,0);
		else if(op<3)in(l),in(r),in(w),TR.change(1,1,n,l,r,x,w,0);
		else in(l),in(r),in(w),TR.change(1,1,n,l,r,x,w,1);
	}
	dijkstra(st);
	for(Re i=1;i<=n;++i)printf("%lld ",dis[i]==inf?-1:dis[i]);
}
