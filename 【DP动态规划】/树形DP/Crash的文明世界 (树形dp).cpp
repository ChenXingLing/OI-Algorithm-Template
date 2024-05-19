#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=5e4+3,M=153,P=10007;
int n,m,x,y,o,K,jc[M],fto[M],head[N],S[M][M],f[N][M],g[N][M];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int dp=0;x=0;char c=getchar();
    while(c<'0'||c>'9')dp|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=dp?-x:x;
}
inline void dfs1(Re x,Re fa){
	f[x][0]=1;
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa){
			dfs1(to,x),(f[x][0]+=f[to][0])%=P;
			for(Re j=1;j<=K;++j)(f[x][j]+=(f[to][j]+f[to][j-1])%P)%=P;
		}
}
inline void dfs2(Re x,Re fa){
	if(fa){
		fto[0]=(g[fa][0]+f[fa][0]-f[x][0]+P)%P;
		for(Re j=1;j<=K;++j)fto[j]=(g[fa][j]+f[fa][j]-(f[x][j]+f[x][j-1])%P+P)%P;
		g[x][0]=fto[0];
		for(Re j=1;j<=K;++j)g[x][j]=(fto[j]+fto[j-1])%P;
	}
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa)dfs2(to,x);
}
inline void Stirling(Re N){
	for(Re i=0;i<=N;++i)S[i][i]=1;
	for(Re i=1;i<=N;++i)
		for(Re j=1;j<i;++j)
			S[j][i]=(S[j-1][i-1]+j*S[j][i-1]%P)%P;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(K),m=n-1;
	while(m--)in(x),in(y),add(x,y),add(y,x);
	dfs1(1,0),dfs2(1,0),Stirling(K),jc[0]=1;
	for(Re i=1;i<=K;++i)jc[i]=jc[i-1]*i%P;
	for(Re i=1;i<=n;++i){
		Re ans=0;
		for(Re j=0;j<=K;++j)
			(ans+=S[j][K]*jc[j]%P*(f[i][j]+g[i][j])%P)%=P;
		printf("%d\n",ans);
	}
}
