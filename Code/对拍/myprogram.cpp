#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=5e5+3;
const LL inf=4e18+5;
int n,opt,A[N],B[N];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
struct QAQ0{
	int x;LL g[N],S[N],dp[N];
	inline void sakura(){
		for(Re i=1;i<=n;++i)in(x),S[i]=S[i-1]+x,dp[i]=inf;
		dp[0]=0,g[0]=S[0];
		for(Re i=1,p=0;i<=n;++i){
			while(p+1<i&&2*S[p+1]-g[p+1]<=S[i])++p;
			dp[i]=dp[p]+(S[i]-S[p])*(S[i]-S[p]),g[i]=S[p];
//			printf("i=%d, p=%d\n",i,p);
//			for(Re j=0;j<=p;++j)
//				if(dp[i]>=(tmp=dp[j]+(S[i]-S[j])*(S[i]-S[j])))
//					dp[i]=tmp,g[i]=S[j];
		}
//		for(Re i=0;i<=n;++i)printf("dp[%d]=%lld\n",i,dp[i]);
		printf("%lld\n",dp[n]);
	}
}T0;
int main(){
//	freopen("456.txt","r",stdin);
	in(n),in(opt);
	if(n<=5000)T0.sakura();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
