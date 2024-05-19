#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register LL
const int N=3e3+5;
LL p,i,j,n,m,h,t,Q[N],S[N],dp[N][N];
//S_walk[m]=S[n]
//              m                               m
//ans=min(m^2 * ¡Æ(walk[i]-S_walk[m]/m)^2 = m * ¡Æ(walk[i]^2) - S[n]^2
//             i=1                             i=1
//        m
//ans=m * ¡Æ(S[Ri]-S[Li])^2 - S[n]^2 = m * dp[m][n] - S[n]^2
//       i=1
//dp[p][i]=min(dp[p-1][j]+(S[i]-S[j])^2)
//(2*S[i]) * S[j] + (dp[p][i]-S[i]^2) = (dp[p-1][j]+S[j]^2)
//   k     *  x   +         b         =          y
inline LL min(Re a,Re b){return a<b?a:b;}
inline LL X(Re j){return S[j];}
inline LL Y(Re j){return dp[p-1][j]+S[j]*S[j];}
inline long double slope(Re i,Re j){return (long double)(Y(j)-Y(i))/(X(j)-X(i));}
int main(){
    memset(dp,127,sizeof(dp));dp[0][0]=0;
    scanf("%lld%lld",&n,&m);
    for(i=1;i<=n;S[i]+=S[i-1],++i)scanf("%lld",&S[i]);
    for(p=1;p<=m;++p){
    	h=1,t=0,Q[++t]=0,dp[p][0]=0;
	    for(i=1;i<=n;++i){
	        while(h<t&&slope(Q[h],Q[h+1])<2*S[i])++h;
	        dp[p][i]=min(dp[p-1][i],dp[p-1][j=Q[h]]+(S[i]-S[j])*(S[i]-S[j]));
			while(h<t&&slope(Q[t-1],Q[t])>slope(Q[t-1],i))--t;
	        Q[++t]=i;
	    }
	}
    printf("%lld",m*dp[m][n]-S[n]*S[n]);
}
