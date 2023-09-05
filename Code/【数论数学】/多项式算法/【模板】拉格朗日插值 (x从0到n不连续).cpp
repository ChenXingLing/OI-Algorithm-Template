#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=2003+3,P=998244353;
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
int ff[N],gg[N];
inline void mul(Re *f,Re n,Re a0,Re *g){//乘以(x+a0)
	for(Re i=0;i<=n;++i)ff[i]=f[i];
	g[0]=(LL)a0*ff[0]%P;for(Re i=1;i<=n+1;++i)g[i]=((LL)a0*ff[i]%P+ff[i-1])%P;
}
inline void div(Re *g,Re n,Re a0,Re *f){//除以(x+a0)
	for(Re i=0;i<=n;++i)gg[i]=g[i];
	f[n-1]=gg[n];for(Re i=n-2;i>=0;--i)f[i]=(gg[i+1]-(LL)a0*f[i+1]%P+P)%P;
}
int fi[N],fmul[N];
inline void Lagrange(Re *x,Re *y,Re n,Re *F){//拉格朗日插值(x不连续)
	fmul[0]=P-x[0],fmul[1]=1;
	for(Re i=1;i<=n;++i)mul(fmul,i,P-x[i],fmul);
	for(Re i=0;i<=n-1;++i)F[i]=0;
	for(Re i=0;i<=n;++i){
		Re tmp=1;
		for(Re j=0;j<=n;++j)if(i!=j)tmp=(LL)tmp*(x[i]-x[j]+P)%P;
		tmp=(LL)y[i]*Inv(tmp)%P;
		div(fmul,n+1,P-x[i],fi);
		for(Re i=0;i<=n;++i)(F[i]+=(LL)tmp*fi[i]%P)%=P;
	}
}
int n,X,ans,x[N],y[N],F[N];
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(X),--n;
	for(Re i=0;i<=n;++i)in(x[i]),in(y[i]);
	Lagrange(x,y,n,F);
	for(Re i=0,tmp=1;i<=n;++i)(ans+=(LL)F[i]*tmp%P)%=P,tmp=(LL)tmp*X%P;
	printf("%d\n",ans);
}
