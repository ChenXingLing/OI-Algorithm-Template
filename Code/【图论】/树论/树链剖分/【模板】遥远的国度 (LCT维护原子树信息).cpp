#include<algorithm>
#include<cstring>
#include<cstdio>
#include<set>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,inf=2e9;
int n,x,y,z,T,op,root,X[N],Y[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Link_Cut_Tree{
	#define pl tr[p].ps[0]
	#define pr tr[p].ps[1]
	#define pf tr[p].fa
	#define pv tr[p].v
	int Q[N];
	struct QAQ{int v,fa,si,shi,ans,add,tag,ans0,ps[2];multiset<int>SI;}tr[N];
	//shi: 所有实儿子(在该链上的v)
	//si: 子树内所有虚儿子(不在该链上的ans)
	inline void pushup(Re p){
		tr[p].shi=min(pv,min(tr[pl].shi,tr[pr].shi));//只要实的
		tr[p].si=min(*tr[p].SI.begin(),min(tr[pl].si,tr[pr].si));//只要虚的
		tr[p].ans=min(tr[p].shi,tr[p].si);
	}
	inline void updata(Re p){tr[p].tag^=1,swap(pl,pr);}
	inline void updata(Re p,Re v){tr[p].add=1,tr[p].shi=pv=v,tr[p].ans=min(tr[p].shi,tr[p].si);}//只修改实的，虚的不变
	inline void pushdown(Re p){
		if(tr[p].tag){
			if(pl)updata(pl);
			if(pr)updata(pr);
			tr[p].tag=0;
		}
		if(tr[p].add){
			if(pl)updata(pl,pv);
			if(pr)updata(pr,pv);
			tr[p].add=0;
		}
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
		Re x=p,t=0;Q[++t]=x;
		while(nort(x))Q[++t]=x=tr[x].fa;
		while(t)pushdown(Q[t--]);
		for(Re fa;nort(p);rotate(p))
			if(nort(fa=pf))rotate(which(p)==which(fa)?fa:p);
	}
	inline void access(Re p){
		for(Re son=0;p;son=p,p=pf){
			splay(p);
			if(pr)tr[p].SI.insert(tr[pr].ans);
			pr=son;
			if(pr)tr[p].SI.erase(tr[p].SI.lower_bound(tr[pr].ans));
			pushup(p);
		}
	}
	inline void makeroot(Re p){access(p),splay(p),updata(p);}
	inline void link(Re x,Re y){makeroot(x),access(y),splay(y),tr[tr[x].fa=y].SI.insert(tr[x].ans);}
	inline void change(Re x,Re y,Re z){makeroot(x),access(y),splay(y),updata(y,z);}
	inline int ask_son(Re p){access(p),splay(p);return min(pv,*tr[p].SI.begin());}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),T1.tr[0].shi=T1.tr[0].si=inf;
	for(Re i=1;i<n;++i)in(X[i]),in(Y[i]);
	for(Re i=1;i<=n;++i)in(T1.tr[i].v),T1.tr[i].SI.insert(inf),T1.pushup(i);
	for(Re i=1;i<n;++i)T1.link(X[i],Y[i]);
	in(root),T1.makeroot(root);
	while(T--){
		in(op),in(x);
		if(op<2)T1.makeroot(root=x);
		else if(op<3)in(y),in(z),T1.change(x,y,z),T1.makeroot(root);
		else printf("%d\n",T1.ask_son(x));
	}
}
