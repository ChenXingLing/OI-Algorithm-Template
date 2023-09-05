#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=13,inf=2e9;
int n,m,cnt,h[N],can[N],vis[N][N],A[2][N][N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int findmin(Re alpha,Re op);
inline int findmax(Re beta,Re op);
inline int findmin(Re alpha,Re op){
	if(cnt==n*m)return 0;
	Re ans=inf;
	for(Re i=1,j;i<=n;++i)
		if(h[i]<m&&vis[i][j=h[i]+1]==-1&&h[i-1]>=j){
			vis[i][j]=op,++cnt,++h[i];
			ans=min(ans,-A[op][i][j]+findmax(ans+A[op][i][j],op^1));
			vis[i][j]=-1,--cnt,--h[i];
			if(ans<=alpha)return ans;
		}
	return ans;
}
inline int findmax(Re beta,Re op){
	if(cnt==n*m)return 0;
	Re ans=-inf;
	for(Re i=1,j;i<=n;++i)
		if(h[i]<m&&vis[i][j=h[i]+1]==-1&&h[i-1]>=j){
			vis[i][j]=op,++cnt,++h[i];
			ans=max(ans,A[op][i][j]+findmin(ans-A[op][i][j],op^1));
			vis[i][j]=-1,--cnt,--h[i];
			if(ans>=beta)return ans;
		}
	return ans;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m);
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=m;++j)
			in(A[1][i][j]);
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=m;++j)
			in(A[0][i][j]);
	memset(vis,-1,sizeof(vis));
	h[0]=inf; 
	printf("%d\n",findmax(inf,1));
}
