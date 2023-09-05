#include<cstring>
#include<cstdio>
#define LL long long
#define Re register LL
const int N=1e6+5;
LL tmp,i,j,n,a,b,c,h=1,t=0,Q[N],S[N],dp[N];
inline LL max(Re a,Re b){return a>b?a:b;}
//dp[i]=dp[j]+a*(S[i]-S[j])^2+b*(S[i]-S[j])+c
//(-2a*S[i]) * S[j] + (b*S[i]+a*S[i]^2-dp[i]) = (b*S[j]-dp[j]-a*S[j]^2)
//    k      * x    +           b             =             y
inline LL X(Re j){return S[j];}
inline LL Y(Re j){return b*S[j]-dp[j]-a*S[j]*S[j];}
inline long double slope(Re i,Re j){return (long double)(Y(j)-Y(i))/(X(j)-X(i));}
int main(){
	scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
	for(i=1;i<=n;S[i]+=S[i-1],++i)scanf("%lld",&S[i]);
	Q[++t]=0;
	for(i=1;i<=n;++i){
		while(h<t&&slope(Q[h],Q[h+1])<(-2*a*S[i]))++h;
		dp[i]=dp[j=Q[h]]+a*(S[i]-S[j])*(S[i]-S[j])+b*(S[i]-S[j])+c;
		while(h<t&&slope(Q[t-1],Q[t])>slope(Q[t-1],i))--t;
		Q[++t]=i;
	}
	printf("%lld",dp[n]);
}
