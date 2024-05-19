#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=15,M=4100,P=1e8;
int n,m,x,V,ans,A[N],dp[N][M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int judge(Re i,Re j){//判断在第i行放j状态是否合法
	return (A[i]&j)==j//j是A[i]的子集
		&&!(j&j<<1)&&!(j&j>>1);//j里面没有左右相邻的
}
int main(){
	in(n),in(m),V=(1<<m)-1;
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=m;++j)
			in(x),A[i]|=(x<<j-1);
	for(Re j=0;j<=V;++j)if(judge(1,j))dp[1][j]=1;
	for(Re i=2;i<=n;++i)
		for(Re j=0;j<=V;++j)if(judge(i,j))//枚举第i行的状态
			for(Re k=0;k<=V;++k)if(judge(i-1,k)&&!(j&k))//枚举第i-1行的状态
				(dp[i][j]+=dp[i-1][k])%=P;
	for(Re j=0;j<=V;++j)(ans+=dp[n][j])%=P;
	printf("%d\n",ans);
}
