#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm>
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
#define F(x,a,b) for(Re x=a;x<=b;++x)
#define lo(l,r,x) (lower_bound(b+l,b+r+1,x)-b)
using namespace std;
const int N=5e4+3,T=230;
int n,t,x,l,r,o,Q,fu,pt[N],L[T],R[T];LL a[N],b[N],add[T];
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void sak(Re l,Re r,Re p,Re x){F(i,l,r)a[i]+=x;F(i,L[p],R[p])b[i]=a[i];sort(b+L[p],b+R[p]+1);}
inline void change(Re l,Re r,Re x){
	Re p=pt[l],q=pt[r];
	if(p==q)sak(l,r,p,x);
	else{
		F(i,p+1,q-1)add[i]+=x;
		sak(l,R[p],p,x),sak(L[q],r,q,x);
	}
}
inline LL ask(Re l,Re r,LL x){
	Re p=pt[l],q=pt[r];LL ans=0;
	if(p==q){F(i,l,r)ans+=a[i]+add[p]<x;return ans;}
	else{
		F(i,p+1,q-1)ans+=lo(L[i],R[i],x-add[i])-L[i];
		F(i,l,R[p])ans+=a[i]+add[p]<x;
		F(i,L[q],r)ans+=a[i]+add[q]<x;
	}
	return ans;
}
int main(){
	in(n),t=sqrt(Q=n);
	F(i,1,t)L[i]=(i-1)*t+1,R[i]=i*t;
	if(R[t]<n)R[++t]=n,L[t]=R[t-1]+1;
	F(i,1,n)in(x),a[i]=b[i]=x;
	F(i,1,t)F(j,L[i],R[i])pt[j]=i;
	F(i,1,t)sort(b+L[i],b+R[i]+1);
	while(Q--){
		in(o),in(l),in(r),in(x);
		if(o)printf("%lld\n",ask(l,r,(LL)x*x));
		else change(l,r,x);
	}
}
