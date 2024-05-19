#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=5003,M=5e5+3,P=80112002;
int n,m,x,y,o,ans,dp[N],ru[N],chu[N],head[N];
struct QAQ{int to,next;}a[M];queue<int>Q;
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
int main(){
	in(n),in(m);
	while(m--)in(x),in(y),add(x,y),++ru[y],++chu[x];
	for(Re i=1;i<=n;++i)if(!ru[i])dp[i]=1,Q.push(i);
	while(!Q.empty()){
		Re x=Q.front();Q.pop();
		for(Re i=head[x],to;i;i=a[i].next){
			(dp[to=a[i].to]+=dp[x])%=P;
			if(!--ru[to])Q.push(to);
		}
	}
	for(Re i=1;i<=n;++i)if(!chu[i])(ans+=dp[i])%=P;
	printf("%d",ans);
}
