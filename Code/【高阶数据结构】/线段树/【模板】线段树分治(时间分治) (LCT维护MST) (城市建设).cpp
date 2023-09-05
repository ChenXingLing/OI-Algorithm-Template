#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=2e4+3,M=5e4+3;
int n,m,x,y,z,T,op,X[N+M],Y[N+M],last[M];LL v[N+M],Ans[M];
inline void in(int &x){
    Re fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct QWQ{int id,op;QWQ(Re ID=0,Re OP=0){id=ID,op=OP;}};
struct Link_Cut_Tree{
	#define pl tr[p].ps[0]
	#define pr tr[p].ps[1]
	#define pf tr[p].fa
	int size,Q[N+M];QWQ QQ[M*32];LL MST;
	struct QAQ{int mx,fa,tag,ps[2];}tr[N+M];
	inline void pushup(Re p){
		tr[p].mx=p;
		if(pl&&v[tr[pl].mx]>v[tr[p].mx])tr[p].mx=tr[pl].mx;
		if(pr&&v[tr[pr].mx]>v[tr[p].mx])tr[p].mx=tr[pr].mx;
	}
	inline void updata(Re p){swap(pl,pr),tr[p].tag^=1;}
	inline void pushdown(Re p){
		if(tr[p].tag){
			if(pl)updata(pl);
			if(pr)updata(pr);
			tr[p].tag=0;
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
		for(Re son=0;p;son=p,p=pf)
			splay(p),pr=son,pushup(p);
	}
	inline void makeroot(Re x){access(x),splay(x),updata(x);}
	inline int findroot(Re p){
		access(p),splay(p),pushdown(p);
		while(pl)pushdown(p=pl);
		return p;
	}
	inline void split(Re x,Re y){makeroot(x),access(y),splay(y);}
	inline void link(Re x,Re y){makeroot(x),tr[x].fa=y;}
	inline void cut(Re x,Re y){makeroot(x),access(y),splay(y),tr[x].fa=tr[y].ps[0]=0,pushup(y);}
	inline void cut_(Re id){
		makeroot(Y[id]),access(X[id]),splay(X[id]),tr[X[id]].ps[0]=tr[Y[id]].fa=tr[id].ps[0]=tr[id].fa=0,pushup(X[id]);
	}
	inline void link_(Re id){
		makeroot(X[id]),makeroot(Y[id]),tr[X[id]].fa=tr[Y[id]].fa=id;
	}
	inline void MST_link(Re id){
		Re x=X[id],y=Y[id];makeroot(x);
		if(findroot(y)!=x)link(x,id),link(id,y),QQ[++size]=QWQ(id,0),MST+=v[id];
		else{
			Re mx=tr[y].mx;
			if(v[id]<v[mx]){
//				cut(X[mx],mx),cut(mx,Y[mx]),QQ[++size]=QWQ(mx,1);
				cut_(mx),QQ[++size]=QWQ(mx,1);
				link(x,id),link(id,y),QQ[++size]=QWQ(id,0);
//				link_(id),QQ[++size]=QWQ(id,0);
				MST+=v[id]-v[mx];
			}
		}
	}
	inline void back(Re to){
		while(size>to){
			QWQ a=QQ[size--];Re id=a.id;
			if(a.op)link(id,Y[id]),link(X[id],id),MST+=v[id];
//			else cut(id,Y[id]),cut(X[id],id),MST-=v[id];
//			if(a.op)link_(id),MST+=v[id];
			else cut_(id),MST-=v[id];
		}
	}
	#undef pl
	#undef pr
}LCT;
int o,head[M<<2];
struct QAQ{int id,next;LL v;}a[M*32];
inline void add(Re x,Re id,LL v){a[++o].id=id,a[o].v=v,a[o].next=head[x],head[x]=o;}
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	inline void change(Re p,Re L,Re R,Re l,Re r,Re id,LL v){
		if(l>r)return;
		if(l<=L&&R<=r){add(p,id,v);return;}
		if(l<=mid)change(pl,L,mid,l,r,id,v);
		if(r>mid)change(pr,mid+1,R,l,r,id,v);
	}
	inline void dfs(Re p,Re L,Re R){
		Re tmp=LCT.size;
		for(Re i=head[p];i;i=a[i].next)v[a[i].id]=a[i].v,LCT.MST_link(a[i].id);
		if(L==R)Ans[L]=LCT.MST;
		else dfs(pl,L,mid),dfs(pr,mid+1,R);
		LCT.back(tmp);
	}
}T1;
int main(){
// 	freopen("123.txt","r",stdin);
// 	freopen("my.txt","w",stdout);
	in(n),in(m),in(T);
	for(Re i=1;i<=m;++i)in(X[i+n]),in(Y[i+n]),in(x),v[i+n]=x,last[i]=1;
	for(Re i=1;i<=T;++i){
		in(x),in(y);
		T1.change(1,1,T,last[x],i-1,x+n,v[x+n]);
		last[x]=i,v[x+n]=y;
	}
	for(Re i=1;i<=m;++i)T1.change(1,1,T,last[i],T,i+n,v[i+n]);
	T1.dfs(1,1,T);
	for(Re i=1;i<=T;++i)printf("%lld\n",Ans[i]);
}
