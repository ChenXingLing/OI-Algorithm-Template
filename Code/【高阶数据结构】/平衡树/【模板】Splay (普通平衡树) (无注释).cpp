#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
#define LL long long
using namespace std;
const int N=1e5+5;
int x,T,op;
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Splay{
	#define pl tr[p].ps[0]
	#define pr tr[p].ps[1]
	#define pf tr[p].fa
	#define pv tr[p].v
	int O,root;
	struct QAQ{int v,fa,cnt,size,ps[2];}tr[N];
	inline void pushup(Re p){
		if(p)tr[p].size=tr[p].cnt+tr[pl].size+tr[pr].size;
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
	inline void splay(Re p){
		for(Re fa;fa=pf;rotate(p))
			if(tr[fa].fa)rotate(which(p)==which(fa)?fa:p);
		root=p;
	}
	inline int ask_level(Re p,Re x){
		if(x==pv){Re ans=tr[pl].size+1;splay(p);return ans;}
		return x<pv?ask_level(pl,x):tr[pl].size+tr[p].cnt+ask_level(pr,x);
	}
	inline int ask_v(Re p,Re k){
		if(!p)return 0;
		if(k<=tr[pl].size)return ask_v(pl,k);
		Re tmp=tr[pl].size+tr[p].cnt;
		return k<=tmp?pv:ask_v(pr,k-tmp);
	}
	inline int pre(Re p){p=pl;while(pr)p=pr;return p;}
	inline int nex(Re p){p=pr;while(pl)p=pl;return p;}
	inline void insert(Re x){
		Re p=root,fa=0;
		while(p&&pv!=x)fa=p,p=tr[p].ps[x>pv];
		if(p)++tr[p].cnt,pushup(p);
		else{
			tr[p=++O]=(QAQ){x,fa,1,1};
			if(fa)tr[fa].ps[x>tr[fa].v]=p;
		}
		splay(p);
	}
	inline void del(Re x){
		ask_level(root,x);Re p=root;
		if(tr[p].cnt>1){--tr[p].cnt,pushup(p);return;}
		if(!pl&&!pr){root=0;return;}
		if(!pl||!pr){tr[root=pl+pr].fa=0;return;}
		splay(pre(p));
		tr[root].ps[1]=pr,tr[pr].fa=root;
		pushup(root);
	}
	inline int ask_pre(Re x){insert(x);Re ans=tr[pre(root)].v;del(x);return ans;}
	inline int ask_nex(Re x){insert(x);Re ans=tr[nex(root)].v;del(x);return ans;}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(T);
	while(T--){
		in(op),in(x);
		if(op==1)T1.insert(x);
		if(op==2)T1.del(x);
		if(op==3)printf("%d\n",T1.ask_level(T1.root,x));
		if(op==4)printf("%d\n",T1.ask_v(T1.root,x));
		if(op==5)printf("%d\n",T1.ask_pre(x));
		if(op==6)printf("%d\n",T1.ask_nex(x));
	}
}
