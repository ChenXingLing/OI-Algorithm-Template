#include<algorithm>
#include<cstring>
#include<cstdio>
#define R register int
using namespace std;
struct QAQ{int to,next;}a[1505]; 
int m,fa[1505],n,o,w[1505],dp[1505][3],head[1505];
inline void add(int x,int y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
  //dp[i][0] 自己不是守卫，儿子是守卫 
 //dp[i][1] 自己是守卫
//dp[i][2] 自己不是守卫，父亲是守卫 
inline void dfs(int x){
    R i,to,dd=0xfffffff;
    dp[x][1]=w[x];dp[x][2]=0;dp[x][0]=0;
    for(i=head[x];i;i=a[i].next){
        dfs(to=a[i].to);
        dp[x][1]+=min(dp[to][2],dp[to][1]);
    //若x自己是守卫（dp[x][1]）:加上儿子 min(1.to被父亲看守dp[to][2]; 2.to自己是看守dp[to][1]) 
        dp[x][2]+=min(dp[to][0],dp[to][1]);
    //若x被父亲看守（dp[x][2]）：加上儿子 min(1.to被孙子看守dp[to][0]; 2.to自己是看守dp[to][1])
        dp[x][0]+=min(dp[to][0],dp[to][1]);
    //若x被儿子看守（dp[x][0]）:找到树立看守所需花费最小的儿子dd，加上其他的儿子 min(1.to被孙子看守dp[to][0]; 2.to自己是看守dp[to][1]) 
		dd=min(dd,dp[to][1]-min(dp[to][0],dp[to][1]));//维护最小的差值  
    }
    dp[x][0]+=dd;
}
int main(){
	memset(dp,127,sizeof(dp));
    scanf("%d",&n);
    R i,j,a,k,r;
    for(i=1;i<=n;i++){
        scanf("%d%d%d",&a,&k,&m);w[a]=k;
        for(j=1;j<=m;j++)scanf("%d",&r),fa[r]=1,add(a,r);
    }
    for(i=1;i<=n;i++)
        if(!fa[i]){
            dfs(i);
            printf("%d",min(dp[i][1],dp[i][0]));
            return 0;
        }
}
