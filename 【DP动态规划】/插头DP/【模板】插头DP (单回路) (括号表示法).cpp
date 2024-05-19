#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=14,M=1594323+3;
int n,m,o,V,edx,edy,Mi[N],A[N][N];LL ans,dp[2][M];char s[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),Mi[0]=1;
	for(Re i=1;i<=m+1;++i)Mi[i]=Mi[i-1]*3;V=Mi[m+1]-1;
	for(Re i=1;i<=n;++i){
		scanf("%s",s+1);
		for(Re j=1;j<=m;++j)if(!(A[i][j]=(s[j]=='*')))edx=i,edy=j;
	}
//	printf("edx=%d, edy=%d\n",edx,edy);
	dp[o][0]=1;
	for(Re i=1;i<=n;++i){
		o^=1;
		for(Re s=0;s<=V;++s)dp[o][s]=s%3?0:dp[o^1][s/3];
		for(Re j=1;j<=m;++j){
			o^=1;
			for(Re s=0;s<=V;++s)dp[o][s]=0;
			for(Re s=0;s<=V;++s)if(dp[o^1][s]){
				Re L=s/Mi[j-1]%3,U=s/Mi[j+1-1]%3;
				if(A[i][j]){if(!L&&!U)dp[o][s]+=dp[o^1][s];}
				else if(!L&&!U)dp[o][s+Mi[j-1]+2*Mi[j+1-1]]+=dp[o^1][s];
				else if(!L&&U)dp[o][s]+=dp[o^1][s],dp[o][s+U*Mi[j-1]-U*Mi[j+1-1]]+=dp[o^1][s];
				else if(L&&!U)dp[o][s]+=dp[o^1][s],dp[o][s-L*Mi[j-1]+L*Mi[j+1-1]]+=dp[o^1][s];
				else if(L==1&&U==1){
					Re cnt=1;
					for(Re k=j+2;k<=m;++k){
						if(s/Mi[k-1]%3==1)++cnt;
						else if(s/Mi[k-1]%3==2)--cnt;
						if(!cnt){dp[o][s-Mi[j-1]-Mi[j+1-1]-Mi[k-1]]+=dp[o^1][s];break;}//2±ä1
					}
				}
				else if(L==2&&U==2){
					Re cnt=1;
					for(Re k=j-1;k>=1;--k){
						if(s/Mi[k-1]%3==1)--cnt;
						else if(s/Mi[k-1]%3==2)++cnt;
						if(!cnt){dp[o][s-2*Mi[j-1]-2*Mi[j+1-1]+Mi[k-1]]+=dp[o^1][s];break;}//1±ä2
					}
				}
				else if(L==2&&U==1)dp[o][s-2*Mi[j-1]-Mi[j+1-1]]+=dp[o^1][s];
				else if(L==1&&U==2)if(i==edx&&j==edy&&!(s-Mi[j-1]-2*Mi[j+1-1]))ans+=dp[o^1][s];
			}
		}
	}
	printf("%lld\n",ans);
}
