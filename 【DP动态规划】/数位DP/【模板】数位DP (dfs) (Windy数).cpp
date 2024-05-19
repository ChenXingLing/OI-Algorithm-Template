#include<cstring>
#include<cstdio>
#include<cmath>
#define R register int
using namespace std;
int a,b,l,num[12],dp[12][10];
inline int dfs(int len,int up,int ok){
    R i,ed,ans=0;
    if(len<1)return 1;
    if(!ok&&~dp[len][up]&&up!=-7)return dp[len][up];
    ed=ok?num[len]:9;
    for(i=0;i<=ed;i++)if(abs(i-up)>=2)
        ans+=dfs(len-1,(!i&&up==-7)?up:i,ok&&(i==ed));
    if(!ok&&up!=-7)dp[len][up]=ans;
    return ans;
}
inline int sovle(int x){
    l=0;
    while(x)num[++l]=x%10,x/=10;
    return dfs(l,-7,1);
}
int main(){
    scanf("%d%d",&a,&b);
    memset(dp,-1,sizeof(dp));
    printf("%d",sovle(b)-sovle(a-1));
}
