#include<bits/stdc++.h>
using namespace std;
int i,j,ans,a,b,z,n,m,pan[110],w,mi,f[110][110],dis[110];
int main(){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            f[i][j]=0xfffffff;
    for(i=1;i<=n;i++)dis[i]=0xfffffff;
    for(i=1;i<=m;i++){
        scanf("%d%d%d",&a,&b,&z);
        f[a][b]=f[b][a]=z;
    }
    for(i=1;i<=n;i++)dis[i]=f[1][i];
    dis[1]=0;pan[1]=1;
    for(i=1;i<=n;i++){
        w=0;mi=0xfffffff;
        for(j=1;j<=n;j++)if(!pan[j]&&dis[j]<mi)mi=dis[w=j];
        if(!w)break;pan[w]=1;
        for(j=1;j<=n;j++)dis[j]=min(dis[j],dis[w]+f[w][j]);
    }
    for(i=1;i<=n;i++)ans=max(ans,dis[i]);
    if(ans==0xfffffff)printf("-1");
    else printf("%d",ans);
    return 0;
}
