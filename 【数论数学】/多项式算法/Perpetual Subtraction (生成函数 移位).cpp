#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=262144+3,P=998244353,G=3;
int n,invn,invG,f[N],g[N],g0[N],gm[N],f0[N],fm[N],tr[N],jc[N],inv[N],invjc[N];LL m;
template<typename T>inline void in(T &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int mi(Re x,LL k){
	Re s=1;
	while(k){
		if(k&1)s=(LL)s*x%P;
		x=(LL)x*x%P,k>>=1;
	}
	return s;
}
inline int Inv(Re x){return mi(x,P-2);}
inline void NTT(Re *f,Re n,Re op){
	for(Re i=0;i<n;++i)if(i<tr[i])swap(f[i],f[tr[i]]);
	for(Re p=2;p<=n;p<<=1){
		Re len=p>>1,w1=mi(op?invG:G,(P-1)/p);
		for(Re st=0;st<n;st+=p)
			for(Re i=st,base=1;i<=st+len-1;++i){
				Re tmp=(LL)base*f[len+i]%P;
				f[len+i]=(f[i]-tmp+P)%P,(f[i]+=tmp)%=P,base=(LL)base*w1%P;
			}
	}
}
inline void times(Re *f,Re n,Re *g,Re m){
	for(m+=n,n=1;n<=m;n<<=1);invn=Inv(n),invG=Inv(G);
	for(Re i=1;i<n;++i)tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	NTT(f,n,0),NTT(g,n,0);
	for(Re i=0;i<n;++i)f[i]=(LL)f[i]*g[i]%P;
	NTT(f,n,1);
	for(Re i=0;i<=m;++i)f[i]=(LL)f[i]*invn%P;
}
int main(){
//    freopen("123.txt","r",stdin);
    in(n),in(m);
    for(Re i=0;i<=n;++i)in(f0[i]);
    invjc[1]=invjc[0]=inv[1]=jc[1]=jc[0]=1;
    for(Re i=2;i<=n+1;++i)inv[i]=(LL)inv[P%i]*(P-P/i)%P,jc[i]=(LL)jc[i-1]*i%P,invjc[i]=(LL)invjc[i-1]*inv[i]%P;
    
	for(Re i=0;i<=n;++i)f[i]=(LL)jc[n-i]*f0[n-i]%P,g[i]=invjc[i];
    times(f,n,g,n);
	for(Re i=0;i<=n;++i)g0[i]=(LL)f[n-i]*invjc[i]%P;
	
//	for(Re i=0;i<=n;++i)printf("%d ",g0[i]);puts("");
	for(Re i=0;i<=n;++i)gm[i]=(LL)g0[i]*mi(inv[i+1],m)%P;
//	for(Re i=0;i<=n;++i)printf("%d ",gm[i]);puts("");

	memset(f,0,sizeof(f)),memset(g,0,sizeof(g));
	for(Re i=0;i<=n;++i)f[i]=(LL)jc[n-i]*gm[n-i]%P,g[i]=(LL)invjc[i]*((i&1)?P-1:1)%P;
	times(f,n,g,n);
	for(Re i=0;i<=n;++i)fm[i]=(LL)f[n-i]*invjc[i]%P;
	
	for(Re i=0;i<=n;++i)printf("%d ",fm[i]);
}
