#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=25003,M=27;
int n,K,A[N];LL dp[M][N];
inline void in(Re &x){
	int f=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
struct BIT{
	int nowL,nowR,C[N];LL ans;
	inline void add(Re x,Re v){if(!x)return;while(x<=n)C[x]+=v,x+=x&-x;}
	inline int ask(Re x){Re ans=0;while(x)ans+=C[x],x-=x&-x;return ans;}
	inline LL calc(Re L,Re R){
		while(nowR<R)++nowR,ans+=ask(A[nowR]-1),add(A[nowR],1);
		while(nowL>L)--nowL,ans+=nowR-nowL-ask(A[nowL]),add(A[nowL],1);
		while(nowR>R)add(A[nowR],-1),ans-=ask(A[nowR]-1),--nowR;
		while(nowL<L)add(A[nowL],-1),ans-=nowR-nowL-ask(A[nowL]),++nowL;
		return ans;
	}
}TR;
inline void sakura(Re l,Re r,Re L,Re R,Re k){
	if(l>r)return;Re mid=l+r>>1,w=0;LL tmp;
	for(Re j=L;j<=R&&j<mid;++j)
		if((tmp=dp[k-1][j]+TR.calc(j+1,mid))<=dp[k][mid])
			dp[k][mid]=tmp,w=j;
	sakura(l,mid-1,L,w,k),sakura(mid+1,r,w,R,k);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(K);
	for(Re i=1;i<=n;++i)in(A[i]);
	memset(dp,19,sizeof(dp)),dp[0][0]=0;
	TR.nowL=1,TR.nowR=0;
	for(Re k=1;k<=K;++k)sakura(k,n,k-1,n-1,k);
	printf("%lld\n",dp[K][n]);
}
