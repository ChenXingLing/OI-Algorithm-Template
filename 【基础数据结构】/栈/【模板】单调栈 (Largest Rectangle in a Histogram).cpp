#include<algorithm>
#include<cstdio>
int i,n,t,wi,a[100005],Q[100005],W[100005];
long long ans;
int main(){
    while(scanf("%d",&n)!=EOF){
        if(!n)break;
        for(i=1;i<=n;i++)scanf("%d",&a[i]);
        ans=a[n+1]=t=0;
        for(i=1;i<=n+1;i++)
            if(a[i]>Q[t])Q[++t]=a[i],W[t]=1;
            else{
                wi=0;
                while(t&&a[i]<=Q[t])ans=std::max(ans,(long long)(wi+=W[t])*Q[t--]);
                Q[++t]=a[i],W[t]=wi+1;
            }
        printf("%lld\n",ans);
    }
}
