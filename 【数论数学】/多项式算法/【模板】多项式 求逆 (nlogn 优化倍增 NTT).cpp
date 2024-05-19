#include<algorithm>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=262144+3,P=998244353,G=3;
int n,A[N],B[N];
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
int invG,tr[N];
inline void NTT(Re *f,Re n,Re op){
	for(Re i=0;i<n;++i)if(i<tr[i])swap(f[i],f[tr[i]]);
	for(Re p=2;p<=n;p<<=1)
		for(Re st=0,len=p>>1,w1=mi(op?invG:G,(P-1)/p);st<n;st+=p)
			for(Re j=st,base=1;j<=st+len-1;++j){
				Re tmp=(LL)base*f[j+len]%P;
				f[j+len]=(f[j]-tmp+P)%P,(f[j]+=tmp)%=P,base=(LL)base*w1%P;
			}
}
inline void times(Re *f,Re n,Re *g,Re m,Re op=0){
	Re n_=n,m_=m;
	for(m+=n,n=1;n<=m;n<<=1);invG=inv(G);
	for(Re i=n_+1;i<n;++i)f[i]=0;
	for(Re i=m_+1;i<n;++i)g[i]=0;
	for(Re i=1;i<n;++i)tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	NTT(f,n,0),NTT(g,n,0);
	for(Re i=0;i<n;++i)f[i]=(LL)f[i]*g[i]%P*(op?g[i]:1)%P;
	NTT(f,n,1);Re invn=inv(n);
	for(Re i=0;i<=m;++i)f[i]=(LL)f[i]*invn%P;
}
int f[N],g[N];
inline void polyinv(Re *a,Re n,Re *b){
	if(n==0){b[0]=inv(a[0]);return;}
	polyinv(a,n>>1,b);
	for(Re i=0;i<=n;++i)f[i]=a[i],g[i]=b[i];
	times(f,n,g,n,1);
	for(Re i=0;i<=n;++i)b[i]=(2*b[i]%P-f[i]+P)%P;
}
int main(){
//    freopen("123.txt","r",stdin);
	in(n),--n;
	for(Re i=0;i<=n;++i)in(A[i]),A[i]%=P;
	polyinv(A,n,B);
	for(Re i=0;i<=n;++i)printf("%d ",B[i]);
}
