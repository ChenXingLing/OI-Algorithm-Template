#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int ans=inf,ans2=0,n,a[110],f[210][210],g[210][210],s[210]; 
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
    for(int i=n+1;i<=2*n;i++)s[i]=s[i-1]+a[i-n];
    memset(f,-127,sizeof(f)),memset(g,127,sizeof(g));
    for(int i=1;i<=2*n;i++)f[i][i]=0,g[i][i]=0;
    for(int len=2;len<=n;len++)//枚举区间长度
	    for(int l=1;l+len-1<=2*n;l++){//枚举区间左端点
	        int r=l+len-1;
	        for(int k=l;k<r;k++)//枚举中间点
	            f[l][r]=max(f[l][r],f[l][k]+f[k+1][r]+s[r]-s[l-1]),
	            g[l][r]=min(g[l][r],g[l][k]+g[k+1][r]+s[r]-s[l-1]);
	    }
    for(int i=1;i<=n;i++)ans=min(ans,g[i][i+n-1]),ans2=max(ans2,f[i][i+n-1]);
    printf("%d\n%d\n",ans,ans2);
    return 0;
}
