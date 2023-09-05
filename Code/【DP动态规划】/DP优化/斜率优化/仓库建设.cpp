#include<cstring>
#include<cstdio>
#define LL long long
#define Re register LL
const int N=1e6+5;
LL i,j,n,w,h=1,t=0,W[N],P[N],C[N],Q[N],SP[N],SC[N],dp[N];
inline LL min(Re a,Re b){return a<b?a:b;}
//dp[i]=dp[j]+Ci+ ¡ÆPk*(Wi-Wk)=dp[j]+Ci+ Wi* ¡ÆPk - ¡ÆPk*Wk
//dp[i]=dp[j]+Ci+Wi*(SP[i]-SP[j])-(SC[i]-SC[j])
//(Wi) * SP[j] + (dp[i]+SC[i]-Wi*SP[i]) = (dp[j]+SC[j])
// k   *   x   +           b            =       y
inline LL X(Re j){return SP[j];}
inline LL Y(Re j){return dp[j]+SC[j];}
inline long double slope(Re i,Re j){return (long double)(Y(j)-Y(i))/(X(j)-X(i));}
int main(){
    scanf("%lld",&n);
    for(i=1;i<=n;SC[i]=SC[i-1]+W[i]*SP[i],SP[i]+=SP[i-1],++i)scanf("%lld%lld%lld",&W[i],&SP[i],&C[i]);
    Q[++t]=0;
    for(i=1;i<=n;++i){
        while(h<t&&slope(Q[h],Q[h+1])<W[i])++h;
        dp[i]=dp[j=Q[h]]+C[i]+W[i]*(SP[i]-SP[j])-SC[i]+SC[j];
        while(h<t&&slope(Q[t-1],Q[t])>slope(Q[t-1],i))--t;
        Q[++t]=i;
    }
    printf("%lld",dp[n]);
}
