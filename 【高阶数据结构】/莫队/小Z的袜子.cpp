#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm>
#include<cstdio>
#include<cmath>
#define Re register int
#define F(x,a,b) for(Re x=a;x<=b;++x)
#define LL long long
using std::sort;
const int N=5e4+3;
int n,q,t,L,R,ip,fu,len,gs[N],pt[N],co[N];LL ans,gcd,fz[N],fm[N];
struct QAQ{int l,r,id;}Q[N];
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void sakura(Re p,Re x){ans-=(LL)gs[fu=co[p]]*gs[fu],gs[fu]+=x,ans+=(LL)gs[fu]*gs[fu];} 
inline bool cmp(QAQ a,QAQ b){return pt[a.l]==pt[b.l]?a.r<b.r:a.l<b.l;}
inline LL gcd_(LL a,LL b){while(b^=a^=b^=a%=b);return a;}
int main(){
	in(n),in(q),t=sqrt(n);
	F(i,1,n)in(co[i]),pt[i]=i/t+1;
	F(i,1,q)in(Q[i].l),in(Q[i].r),Q[i].id=i;
	sort(Q+1,Q+q+1,cmp);
	L=1,R=0;
	F(i,1,q){
		while(L<Q[i].l)sakura(L++,-1);
		while(L>Q[i].l)sakura(--L,1);
		while(R<Q[i].r)sakura(++R,1);
		while(R>Q[i].r)sakura(R--,-1);
		ip=Q[i].id;
		if(Q[i].l==Q[i].r){fz[ip]=0,fm[ip]=1;continue;}
		fz[ip]=ans-(len=Q[i].r-Q[i].l+1);
		fm[ip]=(LL)len*(len-1);
		gcd=gcd_(fz[ip],fm[ip]),fz[ip]/=gcd,fm[ip]/=gcd;
	}
	F(i,1,q)printf("%lld/%lld\n",fz[i],fm[i]);
}
