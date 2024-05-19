#include<algorithm>
#include<cstring>
#include<cstdio>
#define LD long double
#define LL long long
#define Re register int
using namespace std;
const LL N=2e5+3,inf=1e18;
int n,x,h=1,t,Q[N];LL ans=inf,Ans,D[N],S[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
//S严格递增
//D非严格递减
//F[j]=max(D[i]*S[i]-D[i]*S[j]+D[j]*S[j])
//D[i]*S[j] + F[i]-D[i]*S[i] = D[j]*S[j]
// k  * x   +       b        =     y
//维护上凸壳
inline LL X(Re j){return S[j];}
inline LL Y(Re j){return D[j]*S[j];}
inline LD slope(Re i,Re j){return (LD)(Y(j)-Y(i))/(X(j)-X(i));}
int main(){
//	freopen("123.txt","r",stdin);
	in(n);
	for(Re i=1;i<=n;++i)in(x),S[i]=S[i-1]+x,in(x),D[i+1]=D[i]+x;
	for(Re i=1;i<=n+1;++i)D[i]=D[n+1]-D[i],Ans+=D[i]*(S[i]-S[i-1]);
	for(Re i=1;i<=n;++i){
		LL tmp=-inf;
		while(h<t&&slope(Q[h],Q[h+1])>=D[i])++h;
		if(h<=t)ans=min(ans,Ans-(D[i]*(S[i]-S[Q[h]])+D[Q[h]]*S[Q[h]]));
		while(h<t&&slope(Q[t-1],i)>=slope(Q[t-1],Q[t]))--t;
		Q[++t]=i;
//		for(Re j=1;j<i;++j)tmp=max(tmp,D[i]*(S[i]-S[j])+D[j]*S[j]);
	}
	printf("%lld\n",ans);
}
