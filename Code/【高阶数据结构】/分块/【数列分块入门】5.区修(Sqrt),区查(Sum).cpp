#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
#define F(x,a,b) for(Re x=a;x<=b;++x)
const int N=5e4+3,T=230;
int n,t,x,l,r,Q,fu,pt[N],L[T],R[T],pan[T];LL a[N],S[T];
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void sakura(Re p){
	if(pan[p])return;pan[p]=1,S[p]=0;
	F(i,L[p],R[p])S[p]+=(a[i]=sqrt(a[i])),pan[p]&=(a[i]<=1);
}
inline void change(Re l,Re r){
	Re p=pt[l],q=pt[r];
	if(p==q){F(i,l,r)S[p]-=a[i],a[i]=sqrt(a[i]),S[p]+=a[i];}
	else{
		F(i,p+1,q-1)sakura(i);
		F(i,l,R[p])S[p]-=a[i],a[i]=sqrt(a[i]),S[p]+=a[i];
		F(i,L[q],r)S[q]-=a[i],a[i]=sqrt(a[i]),S[q]+=a[i];
	}
}
inline LL ask(Re l,Re r){
	Re p=pt[l],q=pt[r];LL ans=0;
	if(p==q){F(i,l,r)ans+=a[i];}
	else{
		F(i,p+1,q-1)ans+=S[i];
		F(i,l,R[p])ans+=a[i];
		F(i,L[q],r)ans+=a[i];
	}
	return ans;
}
int main(){
	in(n),t=sqrt(Q=n);
	F(i,1,t)L[i]=(i-1)*t+1,R[i]=i*t;
	if(R[t]<n)R[++t]=n,L[t]=R[t-1]+1;
	F(i,1,n)in(x),a[i]=x;
	F(i,1,t)F(j,L[i],R[i])pt[j]=i,S[i]+=a[j];
	while(Q--){
		in(n),in(l),in(r),in(x);
		if(n)printf("%lld\n",ask(l,r));
		else change(l,r);
	}
}
