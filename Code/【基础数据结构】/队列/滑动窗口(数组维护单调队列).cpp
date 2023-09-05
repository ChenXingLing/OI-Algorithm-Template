#include<algorithm>
#include<cstdio>
const int N=1e6+5;
int n,k,i,h,t,a[N],Q[N],D[N];
int main(){
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
        while(h<=t&&Q[t]>=a[i])t--;Q[++t]=a[i],D[t]=i;
        while(h<t&&D[h]+k-1<i)h++;
        if(i>=k)printf("%d ",Q[h]);
    }
    printf("\n");h=t=0;
    for(i=1;i<=n;i++){
        while(h<=t&&Q[t]<=a[i])t--;Q[++t]=a[i],D[t]=i;
        while(h<t&&D[h]+k-1<i)h++;
        if(i>=k)printf("%d ",Q[h]);
    }
}
