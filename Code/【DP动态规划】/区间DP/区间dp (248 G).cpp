#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int ans,n,a[250],f[250][250]; 
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    memset(f,-127,sizeof(f));
    for(int i=1;i<=n;i++)f[i][i]=a[i],ans=max(ans,a[i]);
    for(int len=2;len<=n;len++)//枚举区间长度
	    for(int l=1;l+len-1<=n;l++){//枚举区间左端点
	        int r=l+len-1;
	        for(int k=l;k<r;k++)//枚举中间点
	            if(f[l][k]==f[k+1][r])
					f[l][r]=max(f[l][r],f[l][k]+1);
			ans=max(ans,f[l][r]);         
	    }
    printf("%d",ans);
    return 0;
}
