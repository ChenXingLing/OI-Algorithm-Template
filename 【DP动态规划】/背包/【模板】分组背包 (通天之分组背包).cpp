#include<bits/stdc++.h>
using namespace std;
int a,i,j,k,T,n,m,f[1010],w[1010],v[1010],id[105][1010];
int main(){
    scanf("%d%d",&T,&n);
    for(i=1;i<=n;i++){
        scanf("%d%d%d",&v[i],&w[i],&a);
        id[a][++id[a][0]]=i;m=max(m,a);
    }
    for(k=1;k<=m;k++)
        for(j=T;j>=0;j--)
            for(i=1;i<=id[k][0];i++){
                a=id[k][i];
                if(j>=v[a])f[j]=max(f[j-v[a]]+w[a],f[j]);
            } 
    printf("%d",f[T]);
    return 0;
}
