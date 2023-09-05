#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=15,M=4100,P=1e8;
int n,m,x,V,ans,A[N],zt[N][M],dp[N][M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int main(){
	in(n),in(m),V=(1<<m)-1;
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=m;++j)
			in(x),A[i]|=(x<<j-1);
	for(Re j=0;j<=V;++j)if(!(j&j<<1)&&!(j&j>>1)){//j里面没有左右相邻的
		for(Re i=1;i<=n;++i)if((A[i]&j)==j)zt[i][++zt[i][0]]=j;//如果j是A[i]的子集
	}
	for(Re j=1;j<=zt[1][0];++j)dp[1][j]=1;
	for(Re i=2;i<=n;++i)
		for(Re j=1;j<=zt[i][0];++j)
			for(Re k=1;k<=zt[i-1][0];++k)if(!(zt[i][j]&zt[i-1][k]))
				(dp[i][j]+=dp[i-1][k])%=P;
	for(Re j=1;j<=zt[n][0];++j)(ans+=dp[n][j])%=P;
	printf("%d\n",ans);
}
