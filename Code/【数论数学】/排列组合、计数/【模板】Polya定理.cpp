#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e6+3,P=1e9+7;
int n,T,pri[N/3];bool pan[N];
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
inline int phi(Re x){
	Re ans=x;
	for(Re i=2;i*i<=x;i++)
		if(x%i==0){
			ans/=i,ans*=i-1;
			while(x%i==0)x/=i;
		}
	if(x>1)ans/=x,ans*=x-1;
	return ans;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(T);
	while(T--){
		in(n);Re ans=0;
		for(Re i=1;i*i<=n;++i)
			if(n%i==0){
				(ans+=(LL)mi(n,i-1)*phi(n/i)%P)%=P;
				if(i!=n/i)(ans+=(LL)mi(n,n/i-1)*phi(i)%P)%=P;
			}
		printf("%d\n",ans);
	}
}
