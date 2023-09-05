#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int n,m,P,T,jc[N];
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
inline int C(Re m,Re n){
	return m>n?0:(LL)jc[n]*inv(jc[m])%P*inv(jc[n-m])%P;
}
inline int Lucas(Re m,Re n){
	return m==0?1:(LL)Lucas(m/P,n/P)*C(m%P,n%P)%P;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(T);
	while(T--){
		in(n),in(m),in(P),jc[0]=1;
		for(Re i=1;i<=P-1;++i)jc[i]=(LL)jc[i-1]*i%P;
		printf("%d\n",Lucas(n,n+m));
	}
}
