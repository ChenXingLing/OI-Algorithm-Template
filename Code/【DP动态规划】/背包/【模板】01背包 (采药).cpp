#include<algorithm>
#include<cstdio>
int T,n,i,j,v[110],w[110],f[1010];
int main(){
    scanf("%d%d",&T,&n);
    for(i=1;i<=n;i++)
        scanf("%d%d",&v[i],&w[i]);
    for(i=1;i<=n;i++)
        for(j=T;j>=v[i];j--)
            f[j]=std::max(f[j],f[j-v[i]]+w[i]);
    printf("%d",f[T]);
    return 0;
}
