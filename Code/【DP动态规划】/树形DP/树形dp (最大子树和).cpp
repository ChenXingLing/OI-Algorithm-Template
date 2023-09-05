#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=16003;
int x,y,o,n,ans=-2147483647,f[N],A[N],head[N];
struct QAQ{int next,to;}a[N<<1];
inline void add(int x,int y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void dfs(int x,int Fa){
    f[x]=A[x];
	for(Re i=head[x],to;i;i=a[i].next)
        if((to=a[i].to)!=Fa)
			dfs(to,x),f[x]+=max(0,f[to]);
	ans=max(ans,f[x]);
}
int main(){
    scanf("%d",&n);
    for(Re i=1;i<=n;i++)scanf("%d",&A[i]);
    for(Re i=1;i<n;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x);
    dfs(1,0);
    printf("%d\n",ans);
}
