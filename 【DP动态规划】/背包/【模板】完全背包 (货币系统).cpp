#include<bits/stdc++.h>
using namespace std;
int T,n,ans,a[105],dp[30005];
int main(){
    scanf("%d",&T);
    while(T--){
    	memset(dp,-127,sizeof(dp));
    	scanf("%d",&n);dp[0]=ans=0;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
		    for(int j=a[i];j<=25000;j++)
		        dp[j]=max(dp[j],dp[j-a[i]]+1);
		for(int i=1;i<=n;++i)ans+=dp[a[i]]==1;
		printf("%d\n",ans);
	}
}
