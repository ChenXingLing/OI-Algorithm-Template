#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=6003;
int n,m,x,y,t,o,Ans,b[N],A[N],pt[N],head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Segment_Tree{
	#define pl (tr[p].lp)
	#define pr (tr[p].rp)
	#define mid ((L+R)>>1)
	int O;
	struct QAQ{int lp,rp,up,down;}tr[N*13*2];
	inline void pushup(Re p){
		tr[p].up=max(tr[pl].up,tr[pr].up);
		tr[p].down=max(tr[pl].down,tr[pr].down);
	}
	inline void change1(Re &p,Re L,Re R,Re x,Re v){
		if(!p)p=++O;
		if(L==R){tr[p].up=max(tr[p].up,v);return;}
		if(x<=mid)change1(pl,L,mid,x,v);
		else change1(pr,mid+1,R,x,v);
		pushup(p);
	}
	inline void change2(Re &p,Re L,Re R,Re x,Re v){
		if(!p)p=++O;
		if(L==R){tr[p].down=max(tr[p].down,v);return;}
		if(x<=mid)change2(pl,L,mid,x,v);
		else change2(pr,mid+1,R,x,v);
		pushup(p);
	}
	inline int ask1(Re p,Re L,Re R,Re l,Re r){
		if(!p)return 0;
		if(l<=L&&R<=r)return tr[p].up;
		Re ans=0;
		if(l<=mid)ans=max(ans,ask1(pl,L,mid,l,r));
		if(r>mid)ans=max(ans,ask1(pr,mid+1,R,l,r));
		return ans;
	}
	inline int ask2(Re p,Re L,Re R,Re l,Re r){
		if(!p)return 0;
		if(l<=L&&R<=r)return tr[p].down;
		Re ans=0;
		if(l<=mid)ans=max(ans,ask2(pl,L,mid,l,r));
		if(r>mid)ans=max(ans,ask2(pr,mid+1,R,l,r));
		return ans;
	}
	inline int merge(Re p,Re q,Re L,Re R){
		if(!p||!q)return p+q;
		if(L==R){tr[p].up=max(tr[p].up,tr[q].up),tr[p].down=max(tr[p].down,tr[q].down);return p;}
		Ans=max(Ans,max(tr[pl].up+tr[tr[q].rp].down,tr[pr].down+tr[tr[q].lp].up));
		pl=merge(pl,tr[q].lp,L,mid);
		pr=merge(pr,tr[q].rp,mid+1,R);
		pushup(p);return p;
	}
}TR;
inline void dfs(Re x,Re fa){
	Re up=0,down=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa){
			dfs(to,x);
			Re tmp1=TR.ask1(pt[to],1,t,1,A[x]-1),tmp2=TR.ask2(pt[to],1,t,A[x]+1,t);
			Ans=max(Ans,max(up+tmp2+1,down+tmp1+1));
			up=max(up,tmp1),down=max(down,tmp2);
			pt[x]=TR.merge(pt[x],pt[a[i].to],1,t);
		}
	TR.change1(pt[x],1,t,A[x],up+1),TR.change2(pt[x],1,t,A[x],down+1);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),m=n-1;
	for(Re i=1;i<=n;++i)in(A[i]),b[i]=A[i];
	sort(b+1,b+n+1),t=unique(b+1,b+n+1)-b;
	for(Re i=1;i<=n;++i)A[i]=lower_bound(b+1,b+t+1,A[i])-b;
	while(m--)in(x),in(y),add(x,y),add(y,x);
	dfs(1,0),printf("%d\n",Ans);
}
