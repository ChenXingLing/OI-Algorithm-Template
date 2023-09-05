#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1048576+3,P=998244353,G=3;
int jc[N],inv[N],invjc[N];
inline void in(Re &x){
	int f=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
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
inline int Inv(Re x){return mi(x,P-2);}
int invG,tr[N];
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
	for(m+=n,n=1;n<=m;n<<=1);invG=Inv(G);
	for(Re i=1;i<n;++i)tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	NTT(f,n,0),NTT(g,n,0);
	for(Re i=0;i<n;++i)f[i]=(LL)f[i]*g[i]%P;
	NTT(f,n,1);Re invn=Inv(n);
	for(Re i=0;i<=m;++i)f[i]=(LL)f[i]*invn%P;
}
int n,m,y[N],f[N],g[N],F[N];
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),jc[0]=jc[1]=inv[1]=invjc[0]=invjc[1]=1;
	for(Re i=2;i<=n;++i)inv[i]=(LL)inv[P%i]*(P-P/i)%P,jc[i]=(LL)jc[i-1]*i%P,invjc[i]=(LL)invjc[i-1]*inv[i]%P;
	for(Re i=0;i<=n;++i)in(y[i]),g[i]=(LL)y[i]*((n-i&1)?P-1:1)%P*invjc[i]%P*invjc[n-i]%P;
	for(Re i=0;i<=(n<<1);++i)f[i]=Inv(m-n+i);
	times(f,n<<1,g,n);Re tmp=1;
	for(Re i=m-n;i<=m;++i)tmp=(LL)tmp*i%P;
	for(Re i=0;i<=n;tmp=(LL)tmp*Inv(m-n+i)%P,++i,tmp=(LL)tmp*(m+i)%P)F[i]=(LL)tmp*f[n+i]%P;
	for(Re i=m;i<=m+n;++i)printf("%d ",F[i-m]);
}
