#include<cstdio>
#define R register int
int n,t,x,len,ans[100000],pan[120005];
void cf(int x){
    R i,j;
    for(i=1;i<=len;i++)ans[i]*=x;
    len+=6;
    for(i=1;i<=len;i++)ans[i+1]+=ans[i]/10,ans[i]%=10;
    while(!ans[len])len--;
}
int main(){
    scanf("%d",&n);R i,j;len=ans[1]=1;
    for(i=2;i<=2*n;i++)
        if(pan[i]==0){
            x=i;t=0;
            while(x<=2*n){t+=2*n/x-n/x-(n+1)/x;x*=i;}
            while(t--)cf(i);
            for(j=i;j<=2*n/i;j++)pan[i*j]=1;
        }
    for(i=len;i>=1;i--)printf("%d",ans[i]);
}
