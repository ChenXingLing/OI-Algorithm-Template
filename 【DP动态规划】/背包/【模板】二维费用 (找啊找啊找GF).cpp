#include<algorithm>
#include<cstdio>
using namespace std;
int tmp,T1,T2,x,y,n,i,j,k,v1[105],v2[105],w[105],dp[105][105],ans[105][105];
int main(){
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%d%d%d",&v1[i],&v2[i],&w[i]);
    scanf("%d%d",&T1,&T2);
    for(i=1;i<=n;++i)
        for(j=T1;j>=v1[i];--j)
            for(k=T2;k>=v2[i];--k){
            	if(dp[j][k]<(tmp=dp[j-v1[i]][k-v2[i]]+1)){
            		dp[j][k]=tmp;
            		ans[j][k]=ans[j-v1[i]][k-v2[i]]+w[i];
				}
				else if(dp[j][k]==tmp)ans[j][k]=min(ans[j][k],ans[j-v1[i]][k-v2[i]]+w[i]);
            }
    printf("%d",ans[T1][T2]);
}
