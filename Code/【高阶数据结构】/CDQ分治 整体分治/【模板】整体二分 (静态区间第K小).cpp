#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
#define LL long long
using namespace std;
const int N=2e5+3,M=2e5+3,inf=1e9;
int n,x,y,z,T,cnt,Ans[M];char op;
struct QAQ{int l,r,k,op,id;}Q[N+M],Q1[N+M],Q2[N+M];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct BIT{
	int C[N];
	inline void add(Re x,Re v){while(x<=n)C[x]+=v,x+=x&-x;}
	inline int ask_(Re x){Re ans=0;while(x)ans+=C[x],x-=x&-x;return ans;}
	inline int ask(Re l,Re r){return ask_(r)-ask_(l-1);}
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
			if(Q[i].k<=mid)Q1[++m1]=Q[i],T1.add(Q[i].id,1);
			else Q2[++m2]=Q[i];
		}
		else{
			Re tmp=T1.ask(Q[i].l,Q[i].r);
			if(Q[i].k<=tmp)Q1[++m1]=Q[i];
			else Q[i].k-=tmp,Q2[++m2]=Q[i];
		}
	for(Re i=1;i<=m1;++i)if(Q1[i].op&1)T1.add(Q1[i].id,-1);
	for(Re i=1;i<=m1;++i)Q[L+i-1]=Q1[i];
	for(Re i=1;i<=m2;++i)Q[L+m1+i-1]=Q2[i];
	sakura(l,mid,L,L+m1-1);
	sakura(mid+1,r,L+m1,R);
}
int main(){
	freopen("123.txt","r",stdin);
	in(n),in(T);
	for(Re i=1;i<=n;++i)in(x),Q[++cnt]=(QAQ){0,0,x,1,i};
	for(Re i=1;i<=T;++i)in(x),in(y),in(z),Q[++cnt]=(QAQ){x,y,z,2,i};
	sakura(-inf,inf,1,cnt);
	for(Re i=1;i<=T;++i)printf("%d\n",Ans[i]);
}
