#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,inf=2e9;
int n,m,x,y,o,T,op,A[N],co[N],fa[N],head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Queue{
	priority_queue<int>Q,D;
	inline void insert(Re x){Q.push(x);}
	inline void erase(Re x){if(Q.top()==x)Q.pop();else D.push(x);}
	inline int top(){
		while(!Q.empty()&&!D.empty()&&Q.top()==D.top())Q.pop(),D.pop();
		return Q.empty()?-inf:Q.top();
	}
};
struct Link_Cut_Tree{
	#define pl tr[p].ps[0]
	#define pr tr[p].ps[1]
	#define pf tr[p].fa
	struct QAQ{int fa,max,ps[2];}tr[N];Queue si[N];
	inline void pushup(Re p){
		tr[p].max=max(max(A[p],si[p].top()),max(tr[pl].max,tr[pr].max));
	}
	inline int which(Re p){return tr[pf].ps[1]==p;}
	inline int nort(Re p){return tr[pf].ps[0]==p||tr[pf].ps[1]==p;}
	inline void connect(Re p,Re fa,Re o){tr[pf=fa].ps[o]=p;}
	inline void rotate(Re p){
		Re fa=pf,fas=which(p);
		Re pa=tr[fa].fa,pas=which(fa);
		Re x=tr[p].ps[fas^1];
		if(nort(fa))tr[pa].ps[pas]=p;pf=pa;
		connect(x,fa,fas),connect(fa,p,fas^1);
		pushup(fa),pushup(p);
	}
	inline void splay(Re p){
		for(Re fa;nort(p);rotate(p))
			if(nort(fa=pf))rotate(which(p)==which(fa)?fa:p);
	}
	inline void access(Re p){
		for(Re son=0;p;son=p,p=pf)
			splay(p),si[p].insert(tr[pr].max),pr=son,si[p].erase(tr[pr].max),pushup(p);
	}
	inline void link(Re p,Re fa){
		access(p),splay(p),access(fa),splay(fa),si[pf=fa].insert(tr[p].max),pushup(fa);
	}
	inline void cut(Re p,Re fa){
		access(p),splay(p),splay(fa),pf=tr[fa].ps[1]=0,pushup(fa);
	}
	inline int ask(Re p){
		access(p),splay(p);while(pl)p=pl;splay(p);return tr[pr].max;
	}
	inline void change(Re p,Re v){
		access(p),splay(p),A[p]=v,pushup(p);
	}
}LCT[2];
inline void dfs(Re x,Re Fa){
	LCT[0].tr[x].max=LCT[1].tr[x].max=A[x];
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=Fa)dfs(to,x);
	LCT[co[x]].link(x,fa[x]=Fa);
}
int main(){
//    freopen("123.txt","r",stdin);
    in(n),m=n-1,LCT[0].tr[0].max=LCT[1].tr[0].max=-inf;
    while(m--)in(x),in(y),add(x,y),add(y,x);
    for(Re i=1;i<=n;++i)in(co[i]);
    for(Re i=1;i<=n;++i)in(A[i]);
    in(T),dfs(1,n+1);
    while(T--){
    	in(op),in(x);
    	if(op<1)printf("%d\n",LCT[co[x]].ask(x));
    	else if(op<2)LCT[co[x]].cut(x,fa[x]),LCT[co[x]^=1].link(x,fa[x]);
    	else in(y),LCT[co[x]].change(x,y);
	}
}
