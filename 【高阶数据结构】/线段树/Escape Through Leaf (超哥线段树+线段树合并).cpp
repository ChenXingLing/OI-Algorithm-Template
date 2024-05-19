#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int n,m,x,y,o,cnt,k[N],A[N],B[N],pt[N],head[N];LL b[N],dp[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Segment_Tree{
	#define pl tr[p].lp
	#define pr tr[p].rp
	#define mid ((L+R)>>1)
	int O;
	struct QAQ{int id,lp,rp;}tr[N*18*2*2];
	inline LL y(Re id,Re x){return (LL)k[id]*x+b[id];}
	inline void change(Re &p,Re L,Re R,Re id){
		if(!p){tr[p=++O].id=id;return;}
		if(L==R){if(y(id,L)<y(tr[p].id,L))tr[p].id=id;return;}
		if(k[id]>k[tr[p].id]){
			if(y(id,mid)<y(tr[p].id,mid))change(pr,mid+1,R,tr[p].id),tr[p].id=id;
			else change(pl,L,mid,id);
		}
		else{
			if(y(id,mid)<y(tr[p].id,mid))change(pl,L,mid,tr[p].id),tr[p].id=id;
			else change(pr,mid+1,R,id);
		}
	}
	inline LL ask(Re p,Re L,Re R,Re x){
		if(!p)return 1e18;
		if(L==R)return y(tr[p].id,x);
		LL ans=y(tr[p].id,x);
		if(x<=mid)return min(ans,ask(pl,L,mid,x));
		else return min(ans,ask(pr,mid+1,R,x));
	}
	inline int merge(Re p,Re q,Re L,Re R){
		if(!p||!q)return p+q;
		if(L==R){if(y(tr[p].id,L)>y(tr[q].id,L))tr[p].id=tr[q].id;return p;}
		pl=merge(pl,tr[q].lp,L,mid);
		pr=merge(pr,tr[q].rp,mid+1,R);
		change(p,L,R,tr[q].id);
		return p;
	}
}TR;
inline void dfs(Re x,Re fa){
	Re son=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa)son=1,dfs(to,x),pt[x]=TR.merge(pt[x],pt[to],-N,N);
	k[++cnt]=B[x],dp[x]=b[cnt]=son?TR.ask(pt[x],-N,N,A[x]):0;
	TR.change(pt[x],-N,N,cnt);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),m=n-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	for(Re i=1;i<=n;++i)in(B[i]);
	while(m--)in(x),in(y),add(x,y),add(y,x);
	dfs(1,0);
	for(Re i=1;i<=n;++i)printf("%lld\n",dp[i]);
}
