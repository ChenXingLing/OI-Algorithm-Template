#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,inf=2e9,logN=17;
int n,m,o,x,y,T,op,lastans,A[N],head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int pt[N<<1];
struct Segment_Tree{
	#define pl tr[p].lp
	#define pr tr[p].rp
	#define mid (L+R>>1)
	int O;
	struct QAQ{int S,lp,rp;}tr[N*60];
	inline void change(Re &p,Re L,Re R,Re x,Re v){
		if(!p)p=++O;
		if(L==R){tr[p].S+=v;return;}
		if(x<=mid)change(pl,L,mid,x,v);
		else change(pr,mid+1,R,x,v);
		tr[p].S=tr[pl].S+tr[pr].S;
	}
	inline int ask(Re p,Re L,Re R,Re l,Re r){
		if(!p)return 0;
		if(l<=L&&R<=r)return tr[p].S;
		Re ans=0;
		if(l<=mid)ans+=ask(pl,L,mid,l,r);
		if(r>mid)ans+=ask(pr,mid+1,R,l,r);
		return ans;
	}
}TR;
int rt,sum,gs[N],vis[N],maxp[N],size[N],frt[N][20],fdis[N][20];
inline void getrt(Re x,Re fa){
	size[x]=1,maxp[x]=0;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)
			getrt(to,x),size[x]+=size[to],maxp[x]=max(maxp[x],size[to]);
	maxp[x]=max(maxp[x],sum-size[x]);
	if(maxp[x]<maxp[rt])rt=x;
}
inline void getdis(Re x,Re rt,Re fa,Re d){
	frt[x][++gs[x]]=rt,fdis[x][gs[x]]=d;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to]&&to!=fa)getdis(to,rt,x,d+1);
}
inline void sakura(Re x){
	Re now=sum;vis[x]=1,getdis(x,x,0,0);
	for(Re i=head[x],to;i;i=a[i].next)
		if(!vis[to=a[i].to])
			sum=size[to]>size[x]?now-size[x]:size[to],maxp[rt=0]=inf,getrt(to,0),sakura(rt);
}
inline void change(Re x,Re v){
	TR.change(pt[x],0,n,0,v);
	for(Re i=gs[x];i>=2;--i){
		Re tmp=fdis[x][i-1];
		TR.change(pt[frt[x][i-1]],0,n,tmp,v);
		TR.change(pt[frt[x][i]+n],0,n,tmp,v);
	}
}
inline int ask(Re x,Re K){
	Re ans=TR.ask(pt[x],0,n,0,K);
	for(Re i=gs[x];i>=2;--i){
		Re tmp=fdis[x][i-1];if(tmp>K)continue;
		ans+=TR.ask(pt[frt[x][i-1]],0,n,0,K-tmp);
		ans-=TR.ask(pt[frt[x][i]+n],0,n,0,K-tmp);
	}
	return ans;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),m=n-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	while(m--)in(x),in(y),add(x,y),add(y,x);
	sum=n,maxp[rt=0]=inf,getrt(1,0),sakura(rt);
	for(Re i=1;i<=n;++i)change(i,A[i]);
	while(T--){
		in(op),in(x),in(y),x^=lastans,y^=lastans;
		if(op)change(x,y-A[x]),A[x]=y;
		else printf("%d\n",lastans=ask(x,y));
	}
}
