#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm>
#include<cstdio>
#define Re register int
#define pl tr[p].ps[0]
#define pr tr[p].ps[1]
#define pf tr[p].fa
#define pv tr[p].v
using namespace std;
const int N=1e5+5,inf=2e9;
int T,x,y,n,o,root,a[N];
struct Splay{int v,fa,ps[2],tag,cnt,size;}tr[N];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void pushup(Re p){if(!p)return;tr[p].size=tr[p].cnt+tr[pl].size+tr[pr].size;}
inline void connect(Re p,Re f,Re o){tr[tr[p].fa=f].ps[o]=p;}
inline int which(Re p){return tr[pf].ps[1]==p;}
inline void pushdown(Re p){
	if(tr[p].tag)tr[p].tag=0,swap(pl,pr),tr[pl].tag^=1,tr[pr].tag^=1;
} 
inline void rotate(Re p){
	Re y=pf,ys=which(p);
	Re R=tr[y].fa,Rs=which(y);
	Re B=tr[p].ps[ys^1];
	connect(B,y,ys),connect(y,p,ys^1),connect(p,R,Rs);
	pushup(y),pushup(p);
}
inline void Splay(Re p,Re to){
	for(Re fa;(fa=pf)!=to;rotate(p))
		if(tr[fa].fa!=to)rotate(which(p)==which(fa)?fa:p);
	if(!to)root=p;
}
inline void New(Re x,Re fa){
	tr[++o].v=x,tr[o].fa=fa,tr[o].cnt=tr[o].size=1;
	if(fa)tr[fa].ps[tr[fa].v<x]=o;
}
inline int ask_w(Re p,Re x){
	pushdown(p);
	if(x<=tr[pl].size)return ask_w(pl,x);
	else{
		Re tmp=tr[pl].size+tr[p].cnt;
		return x<=tmp?p:ask_w(pr,x-tmp);
	}
}
inline void build(Re &p,Re L,Re R,Re fa){
	if(L>R)return;
	Re mid=L+R>>1;p=++o;
	pf=fa,pv=a[mid];
	tr[p].cnt=tr[p].size=1;
	build(pl,L,mid-1,p),build(pr,mid+1,R,p);
	pushup(p);
}
inline void reverse(Re l,Re r){
	l=ask_w(root,l-1),r=ask_w(root,r+1);
	Splay(l,0),Splay(r,l);
	tr[tr[r].ps[0]].tag^=1;
}
inline void print(Re p){
	pushdown(p);
	if(pl)print(pl);
	if(pv!=inf&&pv!=-inf)printf("%d ",pv);
	if(pr)print(pr);
}
int main(){
	in(n),in(T);
	a[1]=-inf,a[n+2]=inf;
	for(Re i=2;i<=n+1;++i)a[i]=i-1;
	build(root,1,n+2,0);
	while(T--)in(x),in(y),reverse(x+1,y+1);
	print(root);
}
