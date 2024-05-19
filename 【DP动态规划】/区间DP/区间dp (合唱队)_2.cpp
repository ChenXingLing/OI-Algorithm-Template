#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=1003,P=19650827;
int n,a[N],f[N][N][2];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int main(){
    // freopen("123.txt","r",stdin);
    in(n);
    for(Re i=1;i<=n;++i)in(a[i]),f[i][i][0]=1;
    for(Re len=2;len<=n;++len)
        for(Re i=1;i+len-1<=n;++i){
            Re j=i+len-1;
            (f[i][j][1]=f[i][j-1][1]*(a[j]>a[j-1])+f[i][j-1][0]*(a[j]>a[i]))%=P;//往[i,j-1]的右边加人
            (f[i][j][0]=f[i+1][j][0]*(a[i]<a[i+1])+f[i+1][j][1]*(a[i]<a[j]))%=P;//往[i+1,j]的左边加人
        }
    printf("%d\n",(f[1][n][0]+f[1][n][1])%P);
}
