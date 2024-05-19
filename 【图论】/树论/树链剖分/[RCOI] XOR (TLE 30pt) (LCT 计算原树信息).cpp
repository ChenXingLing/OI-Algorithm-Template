#pragma GCC optimize(3,"Ofast","inline")
#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
#define LL long long
using namespace std;
const int N=1e6+3,M=2e6+3;
int n,m,x,y,T,op,HYJ,Ans,root,A[N];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Link_Cut_Tree{
	#define pl tr[p].ps[0]
	#define pr tr[p].ps[1]
	#define pf tr[p].fa
	int Q[N];
	struct QAQ{int fa,si,ans,tag,shi,yuan,ps[2];}tr[N];
	//tr[p].si: p脚下的虚树子树信息和
	//tr[p].shi: 以p为根的实树信息和
	//tr[p].ans: 以p为根的实+虚树信息和
	inline void pushup(Re p){
		tr[p].shi=A[p]^tr[pl].shi^tr[pr].shi;
		tr[p].ans=A[p]^tr[p].si^tr[pl].ans^tr[pr].ans;
	}
	inline void updata(Re p){swap(pl,pr),tr[p].tag^=1;}
	inline void pushdown(Re p){
		if(tr[p].tag){
			if(pl)updata(pl);
			if(pr)updata(pr);
			tr[p].tag=0;
		}
	}
	inline int nort(Re p){return tr[pf].ps[0]==p||tr[pf].ps[1]==p;}
	inline int which(Re p){return tr[pf].ps[1]==p;}
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
		Re x=p,t=0;Q[++t]=x;
		while(nort(x))Q[++t]=x=tr[x].fa;
		while(t)pushdown(Q[t--]);
		for(Re fa;nort(p);rotate(p))
			if(nort(fa=pf))rotate(which(p)==which(fa)?fa:p);
	}
	inline int access(Re p){
		Re son=0;
		for(;p;son=p,p=pf)
			splay(p),tr[p].si^=tr[pr].ans,tr[p].si^=tr[pr=son].ans,pushup(p);
		return son;
	}
	inline void makeroot(Re p){access(p),splay(p),updata(p);}
	inline int findroot(Re p){
		access(p),splay(p),pushdown(p);
		while(pl)pushdown(p=pl);
		return p;
	}
	inline void split(Re x,Re y){makeroot(x),access(y),splay(y);}
	inline void link(Re x,Re y){
		makeroot(x);
		if(findroot(y)!=x)tr[tr[x].fa=y].si^=tr[x].ans,pushup(y);
	}
	inline int lca(Re x,Re y){access(x);return access(y);}
	
//	inline int ask_son(Re x){access(x),splay(x);return tr[x].si^A[x];}//查询在原树中以x为根的子树信息和（法1）
	inline int ask_son(Re p){access(p);return tr[pr].ans^tr[p].si^A[p];}//查询在原树中以x为根的子树信息和（法2）
}LCT;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(HYJ),in(T),m=n-1,T+=HYJ,root=1;
	for(Re i=1;i<=n;++i)in(A[i]);
	while(m--)in(x),in(y),LCT.link(x,y);
	LCT.makeroot(root);
//	Ans=0;for(Re i=1;i<=n;++i)Ans^=LCT.ask_son(i);
//	printf("%d\n",Ans);return 0;
	while(T--){
		in(op),in(x);
//		if(op<2)LCT.makeroot(root=x),printf("%d\n",Ans);
		if(op<2){
			LCT.makeroot(root=x);Ans=0;
			for(Re i=1;i<=n;++i)Ans^=LCT.ask_son(i);
			printf("%d\n",Ans);
		}
		else if(op<3)in(y),LCT.access(x),LCT.splay(x),A[x]=y,LCT.pushup(x);
		else if(op<4)in(y),printf("%d\n",LCT.lca(x,y));
		else if(op<5)in(y),LCT.split(x,y),printf("%d\n",LCT.tr[y].shi),LCT.makeroot(root);
		else printf("%d\n",LCT.ask_son(x));
		LCT.makeroot(root);
	}
}
