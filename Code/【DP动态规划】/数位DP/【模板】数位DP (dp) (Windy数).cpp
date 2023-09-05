#include<cstdio>
#include<cmath>
#define R register int
using namespace std;
int i,j,k,a,b,l,ans,num[12],dp[12][10];
inline int dpp(int len){
    ans=0;
    for(i=1;i<len;i++)
        for(j=1;j<10;j++)
            ans+=dp[i][j];
    for(j=1;j<num[len];j++)ans+=dp[len][j];
    for(i=len-1;i>0;i--){
        for(j=0;j<num[i];j++)
            if(abs(num[i+1]-j)>=2)ans+=dp[i][j];
        if(abs(num[i]-num[i+1])<2)break;
    }
    if(!i)ans++;
    return ans;
}
inline int sovle(int x){
    l=0;
    while(x)num[++l]=x%10,x/=10;
    return dpp(l);
}
inline int sakura(){
    scanf("%d%d",&a,&b);
    for(i=0;i<10;i++)dp[1][i]=1;
    for(i=2;i<11;i++)
        for(j=0;j<10;j++)
            for(k=0;k<10;k++)
                if(abs(j-k)>=2)
                    dp[i][j]+=dp[i-1][k];
    printf("%d",sovle(b)-sovle(a-1));
}
int QAQWQ=sakura();
int main(){}
