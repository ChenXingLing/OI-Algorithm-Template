#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
#define F(x,a,b) for(Re x=a;x<=b;++x)
const int N=5e4+3,T=230;
int n,t,x,l,r,Q,fu,pt[N],L[T],R[T];LL a[N],S[T],add[T];
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void change(Re l,Re r,Re x){
	Re p=pt[l],q=pt[r];
	if(p==q){F(i,l,r)a[i]+=x;S[p]+=(LL)x*(r-l+1);}
	else{
		F(i,p+1,q-1)add[i]+=x;
		F(i,l,R[p])a[i]+=x;S[p]+=(LL)x*(R[p]-l+1);
		F(i,L[q],r)a[i]+=x;S[q]+=(LL)x*(r-L[q]+1);
	}
}
inline LL ask(Re l,Re r){
	Re p=pt[l],q=pt[r];LL ans=0;
	if(p==q){F(i,l,r)ans+=a[i];ans+=add[p]*(r-l+1);}
	else{
		F(i,p+1,q-1)ans+=S[i]+add[i]*(LL)(R[i]-L[i]+1);
		F(i,l,R[p])ans+=a[i];ans+=add[p]*(LL)(R[p]-l+1);
		F(i,L[q],r)ans+=a[i];ans+=add[q]*(LL)(r-L[q]+1);
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
		if(n)printf("%lld\n",ask(l,r)%(x+1));
		else change(l,r,x);
	}
}
