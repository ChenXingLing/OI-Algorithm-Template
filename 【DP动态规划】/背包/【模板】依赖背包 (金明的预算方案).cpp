#include<algorithm>
#include<cstdio>
using namespace std;
int T,n,i,j,a[65],s,t,r1,r2,r[65][3],v[65],w[65],f[32010];
int main(){
    scanf("%d%d",&T,&n);
    v[0]=0xfffffff;
    for(i=1;i<=n;i++){
        scanf("%d%d%d",&v[i],&s,&a[i]);
        if(a[i])r[a[i]][++r[a[i]][0]]=i;w[i]=v[i]*s;
    }
    for(i=1;i<=n;i++)
        for(j=T;j>=v[i]&&(!a[i]);j--){
            t=j-v[i],r1=r[i][1],r2=r[i][2];
            f[j]=max(f[j],f[t]+w[i]);
            if(v[r1]<=t)f[j]=max(f[j],f[t-v[r1]]+w[i]+w[r1]);
            if(v[r2]<=t)f[j]=max(f[j],f[t-v[r2]]+w[i]+w[r2]);
            if(v[r1]+v[r2]<=t)f[j]=max(f[j],f[t-v[r1]-v[r2]]+w[i]+w[r1]+w[r2]);
        }
    printf("%d",f[T]);
}
