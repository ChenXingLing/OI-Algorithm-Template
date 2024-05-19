#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int 
using namespace std;
const int N=262144+3,P=998244353,G=3,phi=P-1;
inline void in(Re &x){
	int f=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
inline int in_(){
	int f=0;LL x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),x%=P,ch=getchar();
	return x;
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
int invG,tr[N];
inline void NTT(Re *f,Re n,Re op){
	for(Re i=1;i<n;++i)if(i<tr[i])swap(f[i],f[tr[i]]);
	for(Re p=2;p<=n;p<<=1)
		for(Re st=0,len=p>>1,w1=mi(op?invG:G,(P-1)/p);st<n;st+=p)
			for(Re i=st,base=1;i<=st+len-1;++i){
				Re tmp=(LL)f[i+len]*base%P;
				f[i+len]=(f[i]-tmp+P)%P,(f[i]+=tmp)%=P,base=(LL)base*w1%P;
			}
}
inline void times(Re *f,Re n,Re *g,Re m){
	Re n_=n,m_=m;
	for(m+=n,n=1;n<=m;n<<=1);invG=inv(G);
	for(Re i=n_+1;i<n;++i)f[i]=0;
	for(Re i=m_+1;i<n;++i)g[i]=0;
	for(Re i=1;i<n;++i)tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	NTT(f,n,0),NTT(g,n,0);
	for(Re i=0;i<n;++i)f[i]=(LL)f[i]*g[i]%P;
	NTT(f,n,1);Re invn=inv(n);
	for(Re i=0;i<=m;++i)f[i]=(LL)f[i]*invn%P;
}
int c[N];
inline void polymi(Re *x,Re n,Re k,Re *s){
	k%=P,s[0]=1;
	for(Re i=1;i<=n;++i)s[i]=0;
	while(k){
		if(k&1){for(Re i=0;i<=n;++i)c[i]=x[i];times(s,n,c,n);}
		for(Re i=0;i<=n;++i)c[i]=x[i];times(x,n,c,n),k>>=1;
	}
}
int n,K,f[N],g[N];
int main(){
//	freopen("123.txt","r",stdin);
	in(n),--n,K=in_();
	for(Re i=0;i<=n;++i)in(f[i]);
	polymi(f,n,K,g);
	for(Re i=0;i<=n;++i)printf("%d ",g[i]);
}
