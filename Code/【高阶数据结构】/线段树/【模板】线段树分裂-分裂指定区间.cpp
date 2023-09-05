#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=2e5+3;
int n,m,x,y,p,T,op,A[N],pt[N];LL K;
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
	struct QAQ{int lp,rp;LL S;}tr[N*20];
	inline void pushup(Re p){tr[p].S=tr[pl].S+tr[pr].S;}
	inline void build(Re &p,Re L,Re R){
		p=++O;
		if(L==R){tr[p].S=A[L];return;}
		build(pl,L,mid),build(pr,mid+1,R);
		pushup(p);
	}
	inline void change(Re &p,Re L,Re R,Re x,Re v){
		if(!p)p=++O;
		if(L==R){tr[p].S+=v;return;}
		if(x<=mid)change(pl,L,mid,x,v);
		else change(pr,mid+1,R,x,v);
		pushup(p);
	}
	inline LL ask(Re p,Re L,Re R,Re l,Re r){
		if(!p)return 0;
		if(l<=L&&R<=r)return tr[p].S;
		LL ans=0;
		if(l<=mid)ans+=ask(pl,L,mid,l,r);
		if(r>mid)ans+=ask(pr,mid+1,R,l,r);
		return ans;
	}
	inline int ask(Re p,Re L,Re R,LL k){
		if(!p||k>tr[p].S)return -1;
		if(L==R)return L;
		LL tmp=tr[pl].S;
		if(tmp>=k)return ask(pl,L,mid,k);
		else return ask(pr,mid+1,R,k-tmp);
	}
	inline int merge(Re p,Re q,Re L,Re R){//在本题中q不会再次出现，所以可以随意糟蹋而不用新建节点
		if(!p||!q)return p+q;
		if(L==R){tr[p].S+=tr[q].S;return p;}
		pl=merge(pl,tr[q].lp,L,mid);
		pr=merge(pr,tr[q].rp,mid+1,R);
		pushup(p);return p;
	}
	inline void split(Re &p,Re &q,Re L,Re R,Re l,Re r){//把tr[q]中的[l,r]剪切到tr[p]中
		if(!q)return;
		if(l<=L&&R<=r){p=q,q=0;return;}
		p=++O;
		if(l<=mid)split(pl,tr[q].lp,L,mid,l,r);
		if(r>mid)split(pr,tr[q].rp,mid+1,R,l,r);
		pushup(p),pushup(q);
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(m),in(T);
	for(Re i=1;i<=m;++i)in(A[i]);
	T1.build(pt[n=1],1,m);
	while(T--){
		in(op),in(p);
		if(op<1)in(x),in(y),T1.split(pt[++n],pt[p],1,m,x,y);
		else if(op<2)in(x),pt[p]=T1.merge(pt[p],pt[x],1,m),pt[x]=0;
		else if(op<3)in(x),in(y),T1.change(pt[p],1,m,y,x);
		else if(op<4)in(x),in(y),printf("%lld\n",T1.ask(pt[p],1,m,x,y));
		else scanf("%lld",&K),printf("%d\n",T1.ask(pt[p],1,m,K));
	}
}
