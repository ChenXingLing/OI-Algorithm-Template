#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Re register int
using namespace std;
const int N=262144+3,P=167772161,G=3;
int n,m,invn,invG,f[N],g[N],h[N],p[N],tr[N],jc[N],invjc[N];
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
inline void NTT(Re *f,Re n,Re op){
	for(Re i=0;i<n;++i)if(i<tr[i])swap(f[i],f[tr[i]]);
	for(Re p=2;p<=n;p<<=1)
		for(Re st=0,len=p>>1,w1=mi(op?invG:G,(P-1)/p);st<n;st+=p)
			for(Re i=st,base=1;i<=st+len-1;++i){
				Re tmp=(LL)base*f[i+len]%P;
				f[i+len]=(f[i]-tmp+P)%P,f[i]=(f[i]+tmp)%P,base=(LL)base*w1%P;
			}
}
inline void times(Re *f,Re n,Re *g,Re m){
	Re n_=n,m_=m;
	for(m+=n,n=1;n<=m;n<<=1);
	for(Re i=n_+1;i<=n;++i)f[i]=0;//奇怪的初始化
	for(Re i=m_+1;i<=n;++i)g[i]=0;//奇怪的初始化
	for(Re i=1;i<n;++i)tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	NTT(f,n,0),NTT(g,n,0);
	for(Re i=0;i<n;++i)f[i]=(LL)f[i]*g[i]%P;
	NTT(f,n,1);
	for(Re i=0,invn=inv(n);i<=m;++i)f[i]=(LL)f[i]*invn%P;
}
inline void xplus(Re *f,Re *F,Re n,Re c){
	for(Re i=0;i<=n;++i)h[i]=(LL)F[i]*jc[i]%P;
	for(Re i=0,Mi=1;i<=n;++i)p[n-i]=(LL)Mi*invjc[i]%P,Mi=(LL)Mi*c%P;
	times(h,n,p,n);
	for(Re i=0;i<=n;++i)f[i]=(LL)h[n+i]*invjc[i]%P;
}
inline void sakura(Re *f,Re n){
	if(n==1){f[0]=0,f[1]=1;return;}//(x+0)
	if(n&1){
		sakura(f,n-1);
		for(Re i=n;i;--i)f[i]=((LL)f[i]*(n-1)%P+f[i-1])%P;
		f[0]=(LL)f[0]*(n-1)%P;
	}
	else sakura(f,n>>1),xplus(g,f,n>>1,n>>1),times(f,n>>1,g,n>>1);
}
int s[N];
inline void get_Stirling(Re n){
	invjc[1]=invjc[0]=jc[0]=1,invG=inv(G);//注意inv[jc[0]]=1
	if(n==0){s[0]=1;return;}
	for(Re i=1;i<=n;++i)jc[i]=(LL)jc[i-1]*i%P;
	for(Re i=2;i<=n;++i)invjc[i]=(LL)invjc[P%i]*(P-P/i)%P;
	for(Re i=2;i<=n;++i)invjc[i]=(LL)invjc[i]*invjc[i-1]%P;
	sakura(s,n);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),get_Stirling(n);
	for(Re i=0;i<=n;++i)printf("%d ",s[i]);
}
