#include<algorithm>
#include<cstdio>
#define Re register int
using namespace std;
const int N=1e5+3;
int n,m,x,y,z,T,P,op,root,A[N],AA[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Killed_Tree{
	struct QAQ{int to,next;}a[N<<1];
	int o,id_o,fa[N],id[N],idx[N],top[N],son[N],size[N],deep[N],head[N];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	struct Segment_Tree{
		#define pl (p<<1)
		#define pr (p<<1|1)
		#define mid (L+R>>1)
		struct QAQ{int S,l,r,add;}tr[N<<2];
		inline void pushdown(Re p){
			Re v=tr[p].add;
			if(v){
				(tr[pl].S+=v*(tr[pl].r-tr[pl].l+1)%P)%=P,(tr[pl].add+=v)%=P;
				(tr[pr].S+=v*(tr[pr].r-tr[pr].l+1)%P)%=P,(tr[pr].add+=v)%=P;
				tr[p].add=0;
			}
		}
		inline void build(Re p,Re L,Re R){
			tr[p].l=L,tr[p].r=R;
			if(L==R){tr[p].S=AA[L]%P;return;}
			build(pl,L,mid),build(pr,mid+1,R);
			tr[p].S=(tr[pl].S+tr[pr].S)%P;
		}
		inline void change(Re p,Re l,Re r,Re v){
			Re L=tr[p].l,R=tr[p].r;
			if(l<=L&&R<=r){(tr[p].S+=v*(R-L+1)%P)%=P,(tr[p].add+=v)%=P;return;}
			pushdown(p);
			if(l<=mid)change(pl,l,r,v);
			if(r>mid)change(pr,l,r,v);
			tr[p].S=(tr[pl].S+tr[pr].S)%P;
		}
		inline int ask(Re p,Re l,Re r){
			Re L=tr[p].l,R=tr[p].r;
			if(l<=L&&R<=r)return tr[p].S;
			Re ans=0;pushdown(p);
			if(l<=mid)(ans+=ask(pl,l,r))%=P;
			if(r>mid)(ans+=ask(pr,l,r))%=P;
			return ans;
		}
	}TR;
	inline void dfs1(Re x,Re Fa){
		size[x]=1,deep[x]=deep[fa[x]=Fa]+1;
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=Fa){
				dfs1(to,x);
				size[x]+=size[to];
				if(size[to]>size[son[x]])son[x]=to;
			}
	}
	inline void dfs2(Re x,Re rt){
		id[x]=++id_o,idx[id_o]=x,AA[id_o]=A[x],top[x]=rt;
		if(!son[x])return;//叶节点
		dfs2(son[x],rt);
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=fa[x]&&to!=son[x])dfs2(to,to);
	}
	inline void kill(Re rt){dfs1(rt,0),dfs2(rt,rt),TR.build(1,1,n);}
	inline int ask_dis(Re x,Re y){//询问x到y的简单路径上权值之和
		Re ans=0;
		while(top[x]!=top[y]){
			if(deep[top[x]]<deep[top[y]])swap(x,y);
			(ans+=TR.ask(1,id[top[x]],id[x]))%=P;
			x=fa[top[x]];
		}
		if(deep[x]>deep[y])swap(x,y);
		(ans+=TR.ask(1,id[x],id[y]))%=P;
		return ans;
	}
	inline void change_dis(Re x,Re y,Re v){//x到y的简单路径上权值加上v
		while(top[x]!=top[y]){
			if(deep[top[x]]<deep[top[y]])swap(x,y);
			TR.change(1,id[top[x]],id[x],v);
			x=fa[top[x]];
		}
		if(deep[x]>deep[y])swap(x,y);
		TR.change(1,id[x],id[y],v);
	}
	inline int ask_son(Re x){//询问以x为根的子树权值之和
		return TR.ask(1,id[x],id[x]+size[x]-1);
	}
	inline void change_son(Re x,Re v){//以x为根的子树权值加上v
		TR.change(1,id[x],id[x]+size[x]-1,v);
	}
}T1;
int main(){
	in(n),in(T),in(root),in(P),m=n-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	while(m--)in(x),in(y),T1.add(x,y),T1.add(y,x);
	T1.kill(root);
	while(T--){
		in(op);
		if(op<2)in(x),in(y),in(z),T1.change_dis(x,y,z%P);
		else if(op<3)in(x),in(y),printf("%d\n",T1.ask_dis(x,y));
		else if(op<4)in(x),in(z),T1.change_son(x,z%P);
		else in(x),printf("%d\n",T1.ask_son(x));
	}
}
