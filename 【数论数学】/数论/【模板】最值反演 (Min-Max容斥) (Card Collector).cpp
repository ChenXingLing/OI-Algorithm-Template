#include<algorithm>
#include<cstring>
#include<cstdio>
#define LD double
#define LL long long
#define Re register int
using namespace std;
const int N=23,M=1048576+3;
int n,V,cnt[M];LD ans,p[N],Min[M];
inline void in(Re &x){
    int f=0;x=0;char ch=getchar();
    while(ch<'0'||ch>'9')f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=f?-x:x;
}
int main(){
//    freopen("123.txt","r",stdin);
    while(~scanf("%d",&n)){
        V=(1<<n)-1,ans=0;
        for(Re i=1;i<=n;++i)scanf("%lf",&p[i]);
        for(Re s=1;s<=V;++s){
            Min[s]=0,cnt[s]=cnt[s>>1]+(s&1);
            for(Re i=1;i<=n;++i)if(s&(1<<i-1))Min[s]+=p[i];
            Min[s]=1.0/Min[s];
        }
        for(Re t=1;t<=V;++t)ans+=(cnt[t]&1)?Min[t]:-Min[t];
        printf("%lf\n",ans);
    }
}
