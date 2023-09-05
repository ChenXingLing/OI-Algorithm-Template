#include<cstdio>
#define Re register int
const int N=4e6+105;
int i,j,n,m,h=1,t=0,T,ti,ans=2e9,G[N],S[N],Q[N],dp[N];
inline int min(Re a,Re b){return a<b?a:b;}
//                 i
//dp[i]=min(dp[j]+ ∑(i-T[k]))
//                 k=j+1
//dp[i]=dp[j]+(G[i]-G[j])*i-(S[i]-S[j])
//(i) * G[j] + (dp[i]+S[j]-i*G[i]) = (dp[j]+S[j])
// k  *  x   +          b          =      y
inline int X(Re j){return G[j];}
inline int Y(Re j){return dp[j]+S[j];}
inline long double slope(Re i,Re j){return X(i)==X(j)?(Y(j)>Y(i)?2e9:-2e9):(long double)(Y(j)-Y(i))/(long double)(X(j)-X(i));}
int main(){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;T=-min(-T,-ti),++G[ti],S[ti]+=ti,++i)scanf("%d",&ti);
    for(i=1;i<T+m;++i)G[i]+=G[i-1],S[i]+=S[i-1];
    for(i=0;i<m;++i)dp[i]=G[i]*i-S[i];//提前处理dp初始值 
    Q[++t]=0;
    for(i=m;i<T+m;++i){
    	while(h<t&&slope(Q[h],Q[h+1])<=i)++h;
        dp[i]=dp[j=Q[h]]+(G[i]-G[j])*i-S[i]+S[j];
       	while(h<t&&slope(Q[t-1],Q[t])>=slope(Q[t-1],i-m+1))--t;
        Q[++t]=i-m+1;//(j+1)+m<=i
	}
    for(i=T;i<T+m;++i)ans=min(ans,dp[i]);
    printf("%d",ans);
}
