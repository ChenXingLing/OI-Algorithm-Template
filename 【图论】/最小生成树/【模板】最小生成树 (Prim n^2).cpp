#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=5003,M=2e5+3,inf=2e9;
int n,x,y,z,T,ans,pan[N],dis[N],a[N][N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void Prim(){
	for(Re i=0;i<=n;++i)dis[i]=inf;
	Re t=0;dis[1]=0;
	for(Re i=1;i<=n&&t<n;++i){
		Re w=0;
		for(Re j=1;j<=n;++j)if(!pan[j]&&dis[j]<dis[w])w=j;
		pan[w]=1,ans+=dis[w],++t;
		for(Re j=1;j<=n;++j)if(!pan[j])dis[j]=min(dis[j],a[w][j]);
	}
}
int main(){
	in(n),in(T);
	memset(a,127,sizeof(a));
	while(T--)in(x),in(y),in(z),a[x][y]=a[y][x]=min(a[x][y],z);
	Prim();
	printf("%d\n",ans);
}
