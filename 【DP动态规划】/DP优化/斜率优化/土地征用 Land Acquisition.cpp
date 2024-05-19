#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register LL
const int N=5e4+5;
struct QAQ{LL L,W;inline bool operator<(QAQ p)const{return W<p.W;}}a[N];
LL i,j,n,m,h=1,t=0,H=1,T,L[N],W[N],Q[N],dp[N];
inline LL min(Re a,Re b){return a<b?a:b;}
inline LL X(Re j){return -L[j+1];}
inline LL Y(Re j){return dp[j];}
inline long double slope(Re i,Re j){return (long double)(Y(j)-Y(i))/(X(j)-X(i));}
int main(){
    scanf("%lld",&m);
    for(i=1;i<=m;++i)scanf("%lld%lld",&a[i].L,&a[i].W);
    std::sort(a+1,a+m+1);
    for(i=1;i<=m;++i){
    	while(1<=n&&L[n]<=a[i].L)--n;
    	L[++n]=a[i].L,W[n]=a[i].W;
	}
    Q[++t]=0;
    for(i=1;i<=n;++i){
        while(h<t&&slope(Q[h],Q[h+1])<W[i])++h;
        dp[i]=dp[j=Q[h]]+L[j+1]*W[i];
        while(h<t&&slope(Q[t-1],Q[t])>slope(Q[t-1],i))--t;
        Q[++t]=i;
    }
    printf("%lld",dp[n]);
}
