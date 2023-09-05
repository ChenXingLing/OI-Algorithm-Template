#include<cstring>
#include<cstdio>
#define LL long long
#define Re register LL
const int N=5e4+5;
LL i,j,n,L,h=1,t=0,Q[N],S[N],dp[N];
//S[n]=∑C[i]+1, dp[i]=min(dp[j]+(S[i]-(S[j]+L+1))^2)，++L 
//dp[i]=S[i]^2-2*S[i]*L+dp[j]+(S[j]+L)^2-2S[i]*S[j]
//(2*S[i]) * S[j] + (dp[i]-S[i]^2+2S[i]L)=(dp[j]+(S[j]+L)^2)
//   k     *  x   +           b          =        y
inline LL min(Re a,Re b){return a<b?a:b;}
inline LL X(Re j){return S[j];}
inline LL Y(Re j){return dp[j]+(S[j]+L)*(S[j]+L);}
inline long double slope(Re i,Re j){return (long double)(Y(j)-Y(i))/(X(j)-X(i));}
int main(){
    scanf("%lld%lld",&n,&L);++L; 
    for(i=1;i<=n;S[i]+=S[i-1]+1,++i)scanf("%lld",&S[i]);
    Q[++t]=0;//重中之重 
    for(i=1;i<=n;++i){
        while(h<t&&slope(Q[h],Q[h+1])<=2*S[i])++h;//至少要有两个元素 h<t。出队判断时尽量加上等号 
        dp[i]=dp[j=Q[h]]+(S[i]-S[j]-L)*(S[i]-S[j]-L);
        while(h<t&&slope(Q[t-1],Q[t])>=slope(Q[t-1],i))--t;//至少要有两个元素 h<t。入队判断时尽量加上等号 
        Q[++t]=i;
    }
    printf("%lld",dp[n]);
}
