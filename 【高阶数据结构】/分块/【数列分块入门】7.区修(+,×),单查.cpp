#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
#include<cmath>
#define Re register int
#define F(x,a,b) for(Re x=a;x<=b;++x)
const int N=1e5+3,T=320;
int n,t,x,l,r,Q,fu,P=10007,pt[N],L[T],R[T],a[N],add[T],mul[T];
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void spread(Re p){
	F(i,L[p],R[p])(((a[i]*=mul[p])%=P)+=add[p])%=P;
	add[p]=0,mul[p]=1;
}
inline void change(Re l,Re r,Re x){
	Re p=pt[l],q=pt[r];spread(p);
	if(p==q)F(i,l,r)(a[i]+=x)%=P;
	else{
		spread(q);
		F(i,p+1,q-1)(add[i]+=x)%P;
		F(i,l,R[p])(a[i]+=x)%=P;
		F(i,L[q],r)(a[i]+=x)%=P;
	}
}
inline void change2(Re l,Re r,Re x){
	Re p=pt[l],q=pt[r];spread(p);
	if(p==q)F(i,l,r)(a[i]*=x)%=P;
	else{
		spread(q);
		F(i,p+1,q-1)(add[i]*=x)%=P,(mul[i]*=x)%=P;
		F(i,l,R[p])(a[i]*=x)%=P;
		F(i,L[q],r)(a[i]*=x)%=P;
	}
}
inline int ask(Re x){return (a[x]*mul[pt[x]]%P+add[pt[x]])%P;}
int main(){
	in(n),t=sqrt(Q=n);
	F(i,1,t)L[i]=(i-1)*t+1,R[i]=i*t,mul[i]=1;
	if(R[t]<n)R[++t]=n,L[t]=R[t-1]+1,mul[t]=1;
	F(i,1,n)in(a[i]);
	F(i,1,t)F(j,L[i],R[i])pt[j]=i;
	while(Q--){
		in(n),in(l),in(r),in(x);
		if(n>1)printf("%d\n",ask(r));
		else n?change2(l,r,x%P):change(l,r,x%P);
	}
}
