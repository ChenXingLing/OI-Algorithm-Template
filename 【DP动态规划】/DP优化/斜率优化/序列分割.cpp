#include<cstring>
#include<cstdio>
#define LL long long
#define Re register LL
const int N=1e5+5,M=205;
LL tmp,i,j,p,n,K,h,t,Q[N],S[N],to[M][N],dp[M][N];
inline LL max(Re a,Re b){return a>b?a:b;}
//dp[p][i]=dp[p-1][j]+S[j]*(S[i]-S[j])
//(S[i]) * S[j] + (-dp[p][i]) = (S[j]^2-dp[p-1][j])
//  k    *  x   +       b     =          y
inline LL X(Re j){return S[j];}
inline LL Y(Re j){return S[j]*S[j]-dp[p-1][j];}
inline long double slope(Re i,Re j){return X(j)==X(i)?-1e18:(long double)(Y(j)-Y(i))/(X(j)-X(i));}
int main(){
    scanf("%lld%lld",&n,&K);
    for(i=1;i<=n;S[i]+=S[i-1],++i)scanf("%lld",&S[i]);
    for(p=1;p<=K;++p){
        h=1,t=0,Q[++t]=p-1;
        for(i=p;i+K-p<=n;++i){
            while(h<t&&slope(Q[h],Q[h+1])<S[i])++h;
        	dp[p][i]=dp[p-1][to[p][i]=j=Q[h]]+S[j]*(S[i]-S[j]);
       		while(h<t&&slope(Q[t-1],Q[t])>slope(Q[t-1],i))--t;
        	Q[++t]=i;
        }
    }
    printf("%lld\n",dp[K][n]);
    for(i=n,j=K;j>=1;--j)printf("%lld ",i=to[j][i]);
}
