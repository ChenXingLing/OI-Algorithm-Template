#include<algorithm>
#include<cstring>
#include<cstdio>
#include<map>
#define LL long long
#define Re register int
using namespace std;
const int N=13,inf=2e9;
int n,m,cnt,h[N],can[N],vis[N][N],A[2][N][N];
map<LL,int>pan;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline LL Hash(Re op){LL ans=op+1;for(Re i=1;i<=n;++i)ans=ans*11ll+h[i];return ans;}
inline int dfs(Re op){
	if(cnt==n*m)return 0;
	LL H=Hash(op);
	if(pan.find(H)!=pan.end())return pan[H];
	Re ans=op?-inf:inf;
	for(Re i=1,j;i<=n;++i)
		if(h[i]<m&&vis[i][j=h[i]+1]==-1&&h[i-1]>=j){
			vis[i][j]=op,++cnt,++h[i];
			if(op)ans=max(ans,dfs(op^1)+A[op][i][j]);
			else ans=min(ans,dfs(op^1)-A[op][i][j]);
			vis[i][j]=-1,--cnt,--h[i];
		}
	return pan[H]=ans;
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
	printf("%d\n",dfs(1));
}
