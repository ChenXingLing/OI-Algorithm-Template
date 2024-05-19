#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=103,M=13;
int n,m,V,ans,A[N],zt[N][63],cnt[N][63],dp[N][63][63];char s[M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int calc(Re j){//计算j状态里有多少个1 
	Re ans=0;
	for(Re i=1;i<=m;++i)if(j&(1<<i-1))++ans;
	return ans;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),V=(1<<m)-1;
	for(Re i=1;i<=n;++i){
		scanf("%s",s+1);
		for(Re j=1;j<=m;++j)if(s[j]=='P')A[i]|=(1<<j-1);
	}
	zt[0][++zt[0][0]]=0;
	for(Re j=0;j<=V;++j)if(!(j&j<<1)&&!(j&j<<2)&&!(j&j>>1)&&!(j&j>>2)){
		for(Re i=1;i<=n;++i)if((A[i]&j)==j)zt[i][++zt[i][0]]=j,cnt[i][zt[i][0]]=calc(j);
	}
//	for(Re i=0;i<=n;i++)printf("%d:%d\n",i,zt[i][0]);
	memset(dp,-59,sizeof(dp));
	for(Re j=1;j<=zt[1][0];++j)dp[1][j][1]=cnt[1][j];
	for(Re i=2;i<=n;++i)
		for(Re j=1;j<=zt[i][0];++j)
			for(Re k=1;k<=zt[i-1][0];++k)if(!(zt[i][j]&zt[i-1][k]))
				for(Re l=1;l<=zt[i-2][0];++l)
					if(!(zt[i][j]&zt[i-2][l])&&!(zt[i-1][k]&zt[i-2][l]))
						dp[i][j][k]=max(dp[i][j][k],dp[i-1][k][l]+cnt[i][j]);
	for(Re j=1;j<=zt[n][0];++j)
		for(Re k=1;k<=zt[n-1][0];++k)
			ans=max(ans,dp[n][j][k]);
	printf("%d\n",ans);
}
