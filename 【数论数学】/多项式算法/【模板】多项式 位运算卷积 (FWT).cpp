#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Re register int
using namespace std;
const int N=131072+3,P=998244353;
int n,m,inv2,A[N],B[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int inv(Re x){
	Re s=1,k=P-2;
	while(k){
		if(k&1)s=(LL)s*x%P;
		x=(LL)x*x%P,k>>=1;
	}
	return s;
}
int id,f[N],g[N];
inline void FWT(Re *f,Re n,Re op){
	for(Re p=2;p<=n;p<<=1)
		for(Re st=1,len=p>>1;st<n;st+=p)
			for(Re j=st;j<=st+len-1;++j)
				if(id==1)(f[j+len]+=(op?P-f[j]:f[j]))%=P;
				else if(id==2)(f[j]+=(op?P-f[j+len]:f[j+len]))%=P;
				else{
					Re g0=f[j],g1=f[j+len];
					f[j]=(g0+g1)%P,f[j+len]=(g0-g1+P)%P;
					if(op)f[j]=(LL)f[j]*inv2%P,f[j+len]=(LL)f[j+len]*inv2%P;
				}
}
inline void sakura(Re *A,Re *B,Re n,Re id_){
	for(Re i=1;i<=n;++i)f[i]=A[i],g[i]=B[i];id=id_;
	FWT(f,n,0),FWT(g,n,0);
	for(Re i=1;i<=n;++i)f[i]=(LL)f[i]*g[i]%P;
	FWT(f,n,1);
	for(Re i=1;i<=n;++i)printf("%d ",f[i]);puts("");
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),n=(1<<n),inv2=inv(2);
	for(Re i=1;i<=n;++i)in(A[i]);
	for(Re i=1;i<=n;++i)in(B[i]);
	sakura(A,B,n,1),sakura(A,B,n,2),sakura(A,B,n,3);
}
