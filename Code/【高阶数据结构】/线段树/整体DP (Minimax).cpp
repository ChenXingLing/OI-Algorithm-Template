#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=3e5+3,P=998244353;
int n,m,x,ans,inv1e4,f[N],b[N],p[N],A[N],fa[N],ch[N][3];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int mi(Re x,Re k){
	Re s=1;
	while(k){
		if(k&1)s=(LL)s*x%P;
		x=(LL)x*x%P,k>>=1;
	}
	return s;
}
inline int inv(Re x){return mi(x,P-2);}
int pt[N];
struct Segment_Tree{
	#define pl tr[p].lp
	#define pr tr[p].rp
	#define mid ((L+R)>>1)
	int O;
	struct QAQ{int S,lp,rp,mul;}tr[N*19];
	inline void pushup(Re p){
		tr[p].S=(tr[pl].S+tr[pr].S)%P;
	}
	inline void updata(Re p,Re v){
		tr[p].S=(LL)tr[p].S*v%P,tr[p].mul=(LL)tr[p].mul*v%P;
	}
	inline void pushdown(Re p){
		if(tr[p].mul!=1)updata(pl,tr[p].mul),updata(pr,tr[p].mul),tr[p].mul=1;
	}
	inline void change(Re &p,Re L,Re R,Re x,Re v){
		if(!p)p=++O;tr[p].mul=1;
		if(L==R){tr[p].S=v;return;}
		pushdown(p);
		if(x<=mid)change(pl,L,mid,x,v);
		else change(pr,mid+1,R,x,v);
		pushup(p);
	}
	inline int merge(Re p,Re q,Re pv,Re qv,Re v){
//		printf("pv=%d, qv=%d, v=%d\n",pv,qv,v);
		if(!p&&!q)return 0;
		if(!p){updata(q,qv);return q;}
		if(!q){updata(p,pv);return p;}
		pushdown(p),pushdown(q);
		Re plS=tr[pl].S,prS=tr[pr].S,qlS=tr[tr[q].lp].S,qrS=tr[tr[q].rp].S;
//		printf("p:%d,%d q:%d,%d\n",tr[pl].S,tr[pr].S,tr[tr[q].lp].S,tr[tr[q].rp].S);
		pl=merge(pl,tr[q].lp,(pv+(1-v+P)%P*1ll*qrS%P)%P,(qv+(1-v+P)%P*1ll*prS%P)%P,v);
		pr=merge(pr,tr[q].rp,(pv+(LL)v*qlS%P)%P,(qv+(LL)v*plS%P)%P,v);
		pushup(p);
		return p;
	}
	inline void dfs_(Re p,Re L,Re R){
		if(!p)return;
		if(L==R){f[L]=tr[p].S;return;}
		pushdown(p),dfs_(pl,L,mid),dfs_(pr,mid+1,R);
	}
	inline int ask(Re p,Re L,Re R,Re x){
		if(!p)return 0;
		if(L==R)return tr[p].S;
		pushdown(p);
		if(x<=mid)return ask(pl,L,mid,x);
		else return ask(pr,mid+1,R,x);
	}
}T1;
inline void dfs(Re x){
	if(!ch[x][0])T1.change(pt[x],1,m,A[x],1);
	else{
//		printf("x=%d:\n",x);
//		for(Re i=1;i<=m;++i)printf("%d ",T1.ask(pt[x],1,m,i));puts("");
		dfs(ch[x][1]);
		if(ch[x][0]<2)pt[x]=pt[ch[x][1]];
		else dfs(ch[x][2]),pt[x]=T1.merge(pt[ch[x][1]],pt[ch[x][2]],0,0,p[x]);
//		printf("x=%d:\n",x);
//		for(Re i=1;i<=m;++i)printf("%d ",T1.ask(pt[x],1,m,i));puts("");
	}
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),inv1e4=inv(10000);
	for(Re i=1;i<=n;++i)in(fa[i]),ch[fa[i]][++ch[fa[i]][0]]=i;
	for(Re i=1;i<=n;++i)
		if(ch[i][0])in(p[i]),p[i]=(LL)p[i]*inv1e4%P;
		else in(x),b[++m]=A[i]=x;
	sort(b+1,b+m+1);
	for(Re i=1;i<=n;++i)if(!ch[i][0])A[i]=lower_bound(b+1,b+m+1,A[i])-b;
//	for(Re i=1;i<=n;++i)if(!ch[i][0])printf("%d: %d\n",i,A[i]);
	dfs(1),T1.dfs_(1,1,m);
//	for(Re i=1;i<=m;++i)printf("%d ",f[i]);puts("");
	for(Re i=1;i<=m;++i)(ans+=(LL)i*b[i]%P*f[i]%P*f[i]%P)%=P;
	printf("%d\n",ans);
}
