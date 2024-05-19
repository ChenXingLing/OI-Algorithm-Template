#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=15,M=8192+3;
int n,m,o,V,T,A[N][N];LL dp[2][M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(T);
	while(T--){
		in(n),in(m),V=(1<<m+1)-1;
		for(Re i=1;i<=n;++i)
			for(Re j=1;j<=m;++j)
				in(A[i][j]);
		for(Re j=0;j<=V;++j)dp[0][j]=dp[1][j]=0;
		dp[o][0]=1;
		for(Re i=1;i<=n;++i){
			o^=1;
			for(Re s=0;s<=V;++s)dp[o][s]=(s&1)?0:dp[o^1][s>>1];//把线拉下来
			for(Re j=1;j<=m;++j){
				o^=1;
				for(Re s=0;s<=V;++s)dp[o][s]=0;
				for(Re s=0;s<=V;++s)if(dp[o^1][s]){
					Re L=(s>>j-1)&1,U=(s>>j+1-1)&1;
					if(A[i][j]){//可以铺线
						dp[o][s^(1<<j-1)^(1<<j+1-1)]+=dp[o^1][s];//横和竖和左上拐和右下拐
						if(L!=U)dp[o][s]+=dp[o^1][s];//左下拐和右上拐
					}
					else{//不可以铺线
						if(!L&&!U)dp[o][s]+=dp[o^1][s];//无插头才可以转移
					}
				}
			}
		}
		printf("%lld\n",dp[o][0]);
	}
}
