#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
#define LL long long
using namespace std;
const int N=205003;
int n,m,x,y,z,id,ans,id_O,v[N];
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
	struct QAQ{int fa,mx,mxw,tag,ps[2];}tr[N];
	inline void pushup(Re p){
		tr[p].mx=v[p],tr[p].mxw=p;
		if(pl&&tr[pl].mx>tr[p].mx)tr[p].mx=tr[pl].mx,tr[p].mxw=tr[pl].mxw;
		if(pr&&tr[pr].mx>tr[p].mx)tr[p].mx=tr[pr].mx,tr[p].mxw=tr[pr].mxw;
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
	inline void access(Re p){
		for(Re son=0;p;son=p,p=pf)
			splay(p),pr=son,pushup(p);
	}
	inline void makeroot(Re p){access(p),splay(p),updata(p);}
	inline int findroot(Re p){
		access(p),splay(p),pushdown(p);
		while(pl)pushdown(p=pl);
		return p;
	}
	inline void split(Re x,Re y){makeroot(x),access(y),splay(y);}
	inline void link(Re x,Re y){makeroot(x);if(findroot(y)!=x)tr[x].fa=y;}
	inline void cut(Re x,Re y){
		makeroot(x);
		if(findroot(y)==x&&tr[x].fa==y&&!tr[x].ps[1])
			tr[x].fa=tr[y].ps[0]=0,pushup(y);
	}
	inline int judge(Re x,Re y){makeroot(x);return findroot(y)==x;}
	inline void sakura(Re x,Re y,Re z,Re id){
		if(!judge(x,y))link(x,id),link(id,y),ans+=z;
		else{
			split(x,y);Re mx=tr[y].mx,mxw=tr[y].mxw;
			if(z<mx){
				ans+=z-mx,splay(mxw);
				tr[tr[mxw].ps[0]].fa=tr[tr[mxw].ps[1]].fa=0;
				link(x,id),link(id,y);
			}
		}
	}
}LCT;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m);
	while(m--)in(x),in(y),in(z),v[id=++id_O+n]=z,LCT.sakura(x,y,z,id);
	printf("%d\n",ans);
}
