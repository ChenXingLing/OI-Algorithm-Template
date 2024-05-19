#include<cstring>
#include<cstdio>
#define LL long long
#define Re register LL
const int N=1e4+5;
LL i,j,n,h=1,t=0,S,Q[N],ST[N],SF[N],dp[N];
//dp[p][i]=min(dp[p-1][j]+(ST[i]+S*p)*(SF[i]-SF[j]));
//dp[i]=min(dp[i],dp[j]+ST[i]*(SF[i]-SF[j])+S*(SF[n]-SF[j]));
inline LL min(Re a,Re b){return a<b?a:b;}
int main(){
    memset(dp,127,sizeof(dp));dp[0]=0;
    scanf("%lld%lld",&n,&S);
    for(i=1;i<=n;ST[i]+=ST[i-1],SF[i]+=SF[i-1],++i)scanf("%lld%lld",&ST[i],&SF[i]);
    for(i=1;i<=n;++i)
    	for(j=0;j<i;++j)
    		dp[i]=min(dp[i],dp[j]+ST[i]*(SF[i]-SF[j])+S*(SF[n]-SF[j]));
    printf("%lld",dp[n]);
}
