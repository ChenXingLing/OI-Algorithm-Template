#include<algorithm>
#include<cstring>
#include<cstdio>
#define Mat Matrix
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
const LL inf=1e18;
int n,m,o,x,y,T,A[N],head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Matrix{
	LL a[3][3];Mat(){a[1][1]=a[1][2]=a[2][1]=a[2][2]=-inf;}
	inline Mat operator*(const Mat &O)const{
		Mat A;
		for(Re i=1;i<=2;++i)
			for(Re j=1;j<=2;++j)
				for(Re k=1;k<=2;++k)
					A.a[i][j]=max(A.a[i][j],a[i][k]+O.a[k][j]);
		return A;
	}
}G[N];
struct Link_Cut_Tree{
	#define pl tr[p].ps[0]
	#define pr tr[p].ps[1]
	#define pf tr[p].fa
	struct QAQ{int fa,ps[2];}tr[N];Mat TR[N];
	inline void pushup(Re p){
		TR[p]=G[p];
		if(pl)TR[p]=TR[pl]*TR[p];
		if(pr)TR[p]=TR[p]*TR[pr];
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
		for(Re son=0;p;son=p,p=pf){
			splay(p);
			if(pr)G[p].a[1][1]+=max(TR[pr].a[1][1],TR[pr].a[2][1]),G[p].a[1][2]=G[p].a[1][1],G[p].a[2][1]+=TR[pr].a[1][1];
			pr=son;
			if(pr)G[p].a[1][1]-=max(TR[pr].a[1][1],TR[pr].a[2][1]),G[p].a[1][2]=G[p].a[1][1],G[p].a[2][1]-=TR[pr].a[1][1];
			pushup(p);
		}
	}
	inline void change(Re x,Re v){access(x),splay(x),G[x].a[2][1]+=v-A[x],A[x]=v,pushup(x);}//修改x的点权(G[x][1])
	inline LL ask(){splay(1);return max(TR[1].a[1][1],TR[1].a[2][1]);}//询问答案(注意这里取min时应该是看F中的情况而不是G，且注F的摆放位置应满足无实儿子节点处与G中对应值相同)
}T1;
LL g[N][2];//初始时CLT上全为轻边,刚好可以直接求g
inline void dfs(Re x,Re fa){//在剖树时顺手把初始的答案数组g求出来
	g[x][1]=A[x],T1.tr[x].fa=fa;
	for(Re i=head[x],to;i;i=a[i].next)if((to=a[i].to)!=fa)
		dfs(to,x),g[x][0]+=max(g[to][0],g[to][1]),g[x][1]+=g[to][0];
	G[x].a[1][1]=G[x].a[1][2]=g[x][0];
	G[x].a[2][1]=g[x][1],G[x].a[2][2]=-inf;
	T1.pushup(x);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),m=n-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	while(m--)in(x),in(y),add(x,y),add(y,x);
	dfs(1,0);
	while(T--)in(x),in(y),T1.change(x,y),printf("%lld\n",T1.ask());
}
