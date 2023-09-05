#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=2e4+3,inf=2e9;
int n,m,x,y,o,T,head[N];
struct QAQ{int w,to,next;}a[N<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
struct Tree_Diam_DP1{
	int ans,dp[N],size[N];
	inline void dfs(Re x,Re fa){
		size[x]=1,dp[x]=0;
		for(Re i=head[x],to,tmp;i;i=a[i].next)
			if((to=a[i].to)!=fa){
				dfs(to,x),size[x]+=size[to];
				dp[x]=max(dp[x],size[to]);
			}
		if(n-size[x])dp[x]=max(dp[x],n-size[x]);
	}
	inline void sakura(){
		dfs(1,0),dp[ans=0]=inf;
		for(Re i=1;i<=n;++i)if(dp[i]<dp[ans])ans=i;
	}
}T1;
int main(){
	in(T);
	while(T--){
		memset(head,0,sizeof(head));
		in(n),m=n-1,o=0;
	    while(m--)in(x),in(y),add(x,y,1),add(y,x,1);
	    T1.sakura();
		printf("%d %d\n",T1.ans,T1.dp[T1.ans]);
	}
}
