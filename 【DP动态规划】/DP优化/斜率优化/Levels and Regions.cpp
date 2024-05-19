#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define LL long long
#define LD long double
#define Re register int
using namespace std;
const int N=2e5+3,M=53;
int n,o,k,K,a[N];LL S[N];LD S_[N],SS[N],dp[2][N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
//dp[i] = min( dp[j]-SS[j]+S[j]*S_[j] + SS[i] - S[j]*S_[i] )
//(S_[i]) * S[j] + (dp[i]-SS[i]) = (dp[j]-SS[j]+S[j]*S_[j])
//  k     *  x   +       b       =            y
int h=1,t=0,Q[N];
inline LD X(Re j){return S[j];}
inline LD Y(Re j){return dp[o][j]-SS[j]+S[j]*S_[j];}
inline LD slope(Re i,Re j){return (LD)(Y(j)-Y(i))/(X(j)-X(i));}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(K);
	for(Re i=1;i<=n;++i)
		in(a[i]),S[i]=S[i-1]+a[i],S_[i]=S_[i-1]+1.0/a[i],SS[i]=SS[i-1]+1.0*S[i]/a[i];
	for(Re i=1;i<=n;++i)dp[0][i]=dp[1][i]=1e18;
	dp[0][0]=0;
	for(k=1;k<=K;++k){
		h=1,t=0,Q[++t]=k-1;
		for(Re i=k,j;i<=n;++i){
			while(h<t&&slope(Q[h],Q[h+1])<=S_[i])++h;
        	j=Q[h],dp[o^1][i]=dp[o][j]-SS[j]+S[j]*S_[j]+SS[i]-S[j]*S_[i];
        	while(h<t&&slope(Q[t-1],Q[t])>=slope(Q[t-1],i))--t;
        	Q[++t]=i;
		}
		o^=1;
	}
	printf("%.6Lf",dp[o][n]);
}
