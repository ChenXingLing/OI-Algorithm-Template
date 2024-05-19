#include<algorithm>
#include<cstdio>
#define Re register int
using namespace std;
const int N=103,inf=2e9;
int n,m,x,y,z,T,pan[N][N],dis[N][N];
inline void in(Re &x){
    Re fu=0;x=0;char ch=getchar();
    while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=fu?-x:x;
}
int main(){
    in(n),in(m);
    for(Re i=1;i<=n;++i)
        for(Re j=1;j<=n;++j)
            dis[i][j]=inf;
    for(Re i=1;i<=n;++i)dis[i][i]=0,pan[i][i]=1;//初始化自己可以到自己 
    while(m--)in(x),in(y),in(z),pan[x][y]=pan[y][x]=1,dis[x][y]=dis[y][x]=min(dis[x][y],z);
    for(Re k=1;k<=n;++k)//考虑经过前k个点的全源最短路 
        for(Re i=1;i<=n;++i)
            for(Re j=1;j<=n;++j)
            	if(pan[i][k]&&pan[k][j])//以k为中转点进行更新 
                	pan[i][j]=1,dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    for(Re i=1;i<=n;puts(""),++i)
    	for(Re j=1;j<=n;++j)
    		printf("%d ",dis[i][j]);
}
