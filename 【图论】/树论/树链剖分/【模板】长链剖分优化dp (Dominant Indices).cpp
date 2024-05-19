#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e6+3;
int n,m,x,y,o,Sz[N],son[N],Ans[N],dep[N],head[N];int *SZ=Sz,*dp[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void dfs1(Re x,Re fa){
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa){
			dfs1(to,x);
			if(dep[to]>dep[son[x]])son[x]=to;
		}
	dep[x]=dep[son[x]]+1;
}
inline void dfs2(Re x,Re fa){
	dp[x][0]=1;
	if(son[x])dp[son[x]]=dp[x]+1,dfs2(son[x],x),Ans[x]=Ans[son[x]]+1;
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa&&to!=son[x]){
			dp[to]=SZ,SZ+=dep[to],dfs2(to,x);
			for(Re j=1;j<=dep[to];++j){
				dp[x][j]+=dp[to][j-1];
				if(dp[x][j]>dp[x][Ans[x]])Ans[x]=j;
				else if(dp[x][j]==dp[x][Ans[x]])Ans[x]=min(Ans[x],j);
			}
		}
	if(dp[x][Ans[x]]==1)Ans[x]=0;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),m=n-1;
	while(m--)in(x),in(y),add(x,y),add(y,x);
	dfs1(1,0),dp[1]=SZ,SZ+=dep[1],dfs2(1,0);
	for(Re i=1;i<=n;++i)printf("%d\n",Ans[i]);
}
