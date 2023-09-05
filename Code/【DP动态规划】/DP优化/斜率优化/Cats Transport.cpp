#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register LL
const int N=1e5+5;
LL p,n,m,P,w,h,t,H[N],T[N],Q[N],S[N],dp[105][N];
inline LL min(Re a,Re b){return a<b?a:b;}
//                         i
//dp[p][i]=min(dp[p-1][j]+ ¡Æ(T[j]-T[k]))
//                         k=j+1
//dp[p][i]=dp[p-1][j]+(i-j)*T[i]-(S[i]-S[j])
//(T[i]) * j + (dp[p][i]-i*T[i]+S[i]) = (dp[p-1][j]+S[j])
//  k    * x +            b           =        y
inline LL X(Re j){return j;}
inline LL Y(Re j){return dp[p-1][j]+S[j];}
inline long double slope(Re i,Re j){return (long double)(Y(j)-Y(i))/(X(j)-X(i));}
int main(){
	memset(dp,0x3f,sizeof(dp));dp[0][0]=0;
    scanf("%lld%lld%lld",&n,&m,&P);
    for(Re i=2;i<=n;H[i]+=H[i-1],++i)scanf("%lld",&H[i]);
    for(Re i=1;i<=m;T[i]=t-H[w],++i)scanf("%lld%lld",&w,&t);
    std::sort(T+1,T+m+1);
    for(Re i=1;i<=m;++i)S[i]=S[i-1]+T[i];
    for(p=1;p<=P;++p){
    	h=1,t=0,Q[++t]=0,dp[p][0]=0;
	    for(Re i=1;i<=m;++i){
	        while(h<t&&slope(Q[h],Q[h+1])<=T[i])++h;
	        dp[p][i]=min(dp[p-1][i],dp[p-1][j=Q[h]]+(i-j)*T[i]-S[i]+S[j]);
	        if(Y(i)>=0x3f3f3f3f3f3f3f3fll)continue;
			while(h<t&&slope(Q[t-1],Q[t])>=slope(Q[t-1],i))--t;
	        Q[++t]=i;
	    }
	}
    printf("%lld",dp[P][m]); 
}
