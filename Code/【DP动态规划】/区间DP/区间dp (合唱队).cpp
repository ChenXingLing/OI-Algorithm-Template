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
    for(Re len=1;len<n;++len)
        for(Re i=1;i+len-1<=n;++i){
            Re j=i+len-1;
            if(a[j+1]>a[j])(f[i][j+1][1]+=f[i][j][1])%=P;//往[i,j]的右边加人，上一次是在右边 
            if(a[j+1]>a[i])(f[i][j+1][1]+=f[i][j][0])%=P;//往[i,j]的右边加人，上一次是在左边
            if(a[i-1]<a[i])(f[i-1][j][0]+=f[i][j][0])%=P;//往[i,j]的左边加人，上一次是在左边
            if(a[i-1]<a[j])(f[i-1][j][0]+=f[i][j][1])%=P;//往[i,j]的左边加人，上一次是在右边 
        }
    printf("%d\n",(f[1][n][0]+f[1][n][1])%P);
}
