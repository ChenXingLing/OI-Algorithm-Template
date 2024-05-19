#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=2e5+3,inf=1e9;
int n,x,y,z,T,A[N];char op[20];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Splay{
	#define pl (tr[p].ps[0])
	#define pr (tr[p].ps[1])
	#define pf (tr[p].fa)
	#define pv (tr[p].v)
	int O,root,Q[N];queue<int>D;
	struct QAQ{int v,S,fa,max,lmax,rmax,size,ps[2];bool tag,turn;}tr[N];
	inline void pushup(Re p){
		tr[p].S=tr[pl].S+tr[pr].S+pv;
		tr[p].size=tr[pl].size+tr[pr].size+1;
		tr[p].lmax=max(tr[pl].lmax,tr[pl].S+pv+tr[pr].lmax);
		tr[p].rmax=max(tr[pr].rmax,tr[pr].S+pv+tr[pl].rmax);
		tr[p].max=max(tr[pl].rmax+pv+tr[pr].lmax,max(tr[pl].max,tr[pr].max));
	}
	inline void updata(Re p){tr[p].turn^=1,swap(pl,pr),swap(tr[p].lmax,tr[p].rmax);}
	inline void updata(Re p,Re v){
		tr[p].tag=1,tr[p].S=(pv=v)*tr[p].size;
		if(v>0)tr[p].lmax=tr[p].rmax=tr[p].max=tr[p].S;
		else tr[p].lmax=tr[p].rmax=0,tr[p].max=v;
	}
	inline void pushdown(Re p){
		if(tr[p].tag){
			if(pl)updata(pl,pv);
			if(pr)updata(pr,pv);
			tr[p].tag=tr[p].turn=0;
		}
		if(tr[p].turn){
			if(pl)updata(pl);
			if(pr)updata(pr);
			tr[p].turn=0;
		}
	}
	inline int which(Re p){return tr[pf].ps[1]==p;}
	inline void connect(Re p,Re fa,Re o){tr[pf=fa].ps[o]=p;}
	inline void rotate(Re p){
		Re fa=pf,fas=which(p);
		Re pa=tr[fa].fa,pas=which(fa);
		Re x=tr[p].ps[fas^1];
		connect(x,fa,fas),connect(fa,p,fas^1),connect(p,pa,pas);
		pushup(fa),pushup(p);
	}
	inline void splay(Re p,Re to){
		Re x=p,t=0;Q[++t]=x;
		while(tr[x].fa)Q[++t]=x=tr[x].fa;
		while(t)pushdown(Q[t--]);
		for(Re fa;pf!=to;rotate(p))
			if(tr[fa=pf].fa!=to)rotate(which(p)==which(fa)?fa:p);
		if(!to)root=p;
	}
	inline void CL(Re p){
		tr[p].size=tr[p].turn=tr[p].tag=tr[p].lmax=tr[p].rmax=tr[p].S=pv=pf=pl=pr=0,tr[p].max=-inf;
	}
	inline int New(){
		Re p;
		if(D.empty())p=++O;
		else p=D.front(),D.pop();
		CL(p),tr[p].size=1;return p;
	}
	inline void build(Re &p,Re L,Re R,Re fa){
		if(L>R)return;Re mid=(L+R)>>1;p=New(),pv=A[mid],pf=fa;
		build(pl,L,mid-1,p),build(pr,mid+1,R,p);
		pushup(p);
	}
	inline void recycle(Re p){
		if(pl)recycle(pl);
		if(pr)recycle(pr);
		D.push(p),CL(p);
	}
	inline int find(Re p,Re K){
		pushdown(p);
		if(K<=tr[pl].size)return find(pl,K);
		return K<=tr[pl].size+1?p:find(pr,K-tr[pl].size-1);
	}
	inline int split(Re L,Re R){
		Re p=find(root,L-1),q=find(root,R+1);
		splay(p,0),splay(q,p);return tr[q].ps[0];
	}
	inline void insert(Re st,Re m){
		for(Re i=1;i<=m;++i)in(A[i]);
		Re rt=0;build(rt,1,m,0);
		Re p=find(root,st),q=find(root,st+1);
		splay(p,0),splay(q,p);
		connect(rt,q,0),pushup(q),pushup(p);
	}
	inline void erase(Re L,Re R){
		Re p=split(L,R),fa=pf;
		tr[fa].ps[0]=pf=0,recycle(p);
		pushup(fa),pushup(tr[fa].fa);
	}
	inline int ask(Re L,Re R){return tr[split(L,R)].S;}
	inline int ask_max(Re L,Re R){return tr[split(L,R)].max;}
	inline void change(Re L,Re R,Re v){
		Re p=split(L,R);updata(p,v),pushup(pf),pushup(tr[pf].fa);
	}
	inline void reverse(Re L,Re R){
		Re p=split(L,R);
		if(!tr[p].tag)updata(p),pushup(pf),pushup(tr[pf].fa);
	}
}TR;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),TR.tr[0].max=A[1]=A[n+2]=-inf;
	for(Re i=2;i<=n+1;++i)in(A[i]);
	TR.build(TR.root,1,n+2,0);
	while(T--){
		scanf("%s",op);
        if(op[0]=='M'&&op[2]=='X')in(x),in(y),++x,printf("%d\n",TR.ask_max(x,x+y-1));
		else if(op[0]=='G'&&(int)strlen(op)==3)in(x),++x,printf("%d\n",TR.ask(x,x));
		else{
			in(x),in(y),++x;
	        if(op[0]=='I')TR.insert(x,y);
	        if(op[0]=='D')TR.erase(x,x+y-1);
	        if(op[0]=='M')in(z),TR.change(x,x+y-1,z);
	        if(op[0]=='R')TR.reverse(x,x+y-1);
	        if(op[0]=='G')printf("%d\n",TR.ask(x,x+y-1));
		}
	}
}
