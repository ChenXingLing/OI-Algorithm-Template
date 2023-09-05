#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
#define LL long long
using namespace std;
const int N=5e4+3,M=5e4+3,inf=1e9;
int n,x,T,Ans[M];
struct QAQ{int l,r,op,id;LL k;}Q[N+M],Q1[N+M],Q2[N+M];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Segment_Tree{
	#define pl p<<1
	#define pr p<<1|1
	#define Mid (L+R>>1)
	struct QAQ{int CL,add;LL S;}tr[N<<2];
	inline void pushup(Re p){tr[p].S=tr[pl].S+tr[pr].S;}
	inline void updata(Re p,Re L,Re R,Re v){tr[p].S+=v*(R-L+1),tr[p].add+=v;}
	inline void updata_(Re p){tr[p].add=tr[p].S=0,tr[p].CL=1;}
	inline void pushdown(Re p,Re L,Re R){
		if(tr[p].CL)updata_(pl),updata_(pr),tr[p].CL=0;
		if(tr[p].add)updata(pl,L,Mid,tr[p].add),updata(pr,Mid+1,R,tr[p].add),tr[p].add=0;
	}
	inline void change(Re p,Re L,Re R,Re l,Re r,Re v){
		if(l<=L&&R<=r){updata(p,L,R,v);return;}
		pushdown(p,L,R);
		if(l<=Mid)change(pl,L,Mid,l,r,v);
		if(r>Mid)change(pr,Mid+1,R,l,r,v);
		pushup(p);
	}
	inline LL ask(Re p,Re L,Re R,Re l,Re r){
		if(l<=L&&R<=r)return tr[p].S;
		LL ans=0;pushdown(p,L,R);
		if(l<=Mid)ans+=ask(pl,L,Mid,l,r);
		if(r>Mid)ans+=ask(pr,Mid+1,R,l,r);
		return ans;
	}
}T1;
inline void sakura(Re l,Re r,Re L,Re R){
	if(L>R)return;
	if(l==r){
		for(Re i=L;i<=R;++i)if(Q[i].op>1)Ans[Q[i].id]=l;
		return;
	}
	Re mid=l+r>>1,m1=0,m2=0;
	for(Re i=L;i<=R;++i)
		if(Q[i].op&1){
			if(Q[i].k<=mid)Q1[++m1]=Q[i];
			else Q2[++m2]=Q[i],T1.change(1,1,n,Q[i].l,Q[i].r,1);
		}
		else{
			LL tmp=T1.ask(1,1,n,Q[i].l,Q[i].r);
			if(Q[i].k<=tmp)Q2[++m2]=Q[i];
			else Q[i].k-=tmp,Q1[++m1]=Q[i];
		}
	T1.updata_(1);
	for(Re i=1;i<=m1;++i)Q[L+i-1]=Q1[i];
	for(Re i=1;i<=m2;++i)Q[L+m1+i-1]=Q2[i];
	sakura(l,mid,L,L+m1-1);
	sakura(mid+1,r,L+m1,R);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T);
	for(Re i=1;i<=T;++i){
		in(Q[i].op),in(Q[i].l),in(Q[i].r),in(x),Q[i].k=x;
		if(Q[i].op>1)Q[i].id=++Ans[0];
	}
	sakura(-n,n,1,T);
	for(Re i=1;i<=Ans[0];++i)printf("%d\n",Ans[i]);
}
