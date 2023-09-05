#include<algorithm>
#include<cstring>
#include<cstdio>
int ans,T,n,i,j,k,K,t,tmp[55],v[210],w[210],f[5010][55];
int main(){
    scanf("%d%d%d",&K,&T,&n);
    memset(f,-127,sizeof(f));f[0][1]=0;
    for(i=1;i<=n;i++)scanf("%d%d",&v[i],&w[i]);
    for(i=1;i<=n;i++)
        for(j=T;j>=v[i];j--){
            int p1=1,p2=1;k=0;
            while(k<=K){
                if(f[j][p1]>=f[j-v[i]][p2]+w[i])tmp[++k]=f[j][p1++];
                else tmp[++k]=f[j-v[i]][p2++]+w[i];
            }
            for(k=1;k<=K;k++)f[j][k]=tmp[k];
        }
    for(i=1;i<=K;i++)ans+=f[T][i];
    printf("%d",ans);
    return 0;
}
