#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1003,M=1e5+3;
int n,m,x,y,z,T,op,id,id_O,v[N+M],vis[N+M],Ans[M],ID[N][N];
struct Query{int op,x,y;}Q[M];
inline void in(int &x){
    Re fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Link_Cut_Tree{
	#define pl tr[p].ps[0]
	#define pr tr[p].ps[1]
	#define pf tr[p].fa
	int Q[N+M];
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
	inline void link(Re x,Re y){makeroot(x);if(findroot(y)!=x)tr[x].fa=y;}
	inline void cut(Re x,Re y){
		makeroot(x);
		if(findroot(y)==x&&tr[x].fa==y&&!tr[x].ps[1])
			tr[x].fa=tr[y].ps[0]=0,pushup(y);
	}
	inline void MST_link(Re x,Re y,Re id){
		makeroot(x);
		if(findroot(y)!=x)link(x,id),link(id,y);
		else{
			split(x,y);Re mx=tr[y].mx;
			if(v[id]<v[mx]){
				splay(mx);
				tr[tr[mx].ps[0]].fa=tr[tr[mx].ps[1]].fa=0;
				tr[mx].ps[0]=tr[mx].ps[1]=tr[mx].fa=0;
				link(x,id),link(id,y);
			}
		}
	}
	inline int MST_path(Re x,Re y){split(x,y);return v[tr[y].mx];}
}LCT;
struct Kruscal{
	int fa[N];
	struct QAQ{int x,y,z;inline bool operator<(const QAQ &O)const{return z<O.z;}}a[M];
	inline int find(Re x){return x==fa[x]?x:fa[x]=find(fa[x]);}
	inline void sakura(){
		for(Re i=1;i<=n;++i)fa[i]=i;
		for(Re i=1;i<=m;++i)in(x),in(y),in(z),v[ID[x][y]=ID[y][x]=++id_O+n]=z,a[i]=(QAQ){x,y,z};
		for(Re i=1;i<=T;++i)in(op),in(x),in(y),vis[ID[x][y]]|=op>1,Q[i]=(Query){op,x,y};
		sort(a+1,a+m+1);
		for(Re i=1,t=0;t<n-1&&i<=m;++i)
			if(!vis[ID[x=a[i].x][y=a[i].y]]&&find(x)!=find(y))
				fa[find(x)]=find(y),++t,LCT.MST_link(x,y,ID[x][y]);
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),in(T),T1.sakura();
	for(Re i=T;i>=1;--i){
		Re op=Q[i].op,x=Q[i].x,y=Q[i].y;
		if(op&1)Ans[++Ans[0]]=LCT.MST_path(x,y);
		else LCT.MST_link(x,y,ID[x][y]);
	}
	for(Re i=Ans[0];i>=1;--i)printf("%d\n",Ans[i]);
}
