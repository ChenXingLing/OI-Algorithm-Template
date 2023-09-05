#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=12;
int n,m,ct,A[N][N],B[N][N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Steiner_Tree{
	struct PRE{int i,j,s;PRE(Re I=0,Re J=0,Re S=0){i=I,j=J,s=S;}}pre[N][N][1024+3];
	int vis[N][N],dp[N][N][1024+3],wx[4]={-1,0,1,0},wy[4]={0,1,0,-1};
	struct QAQ{int x,y;QAQ(Re X=0,Re Y=0){x=X,y=Y;}};
	queue<QAQ>Q;
	inline void SPFA(Re s){
		while(!Q.empty()){
			QAQ now=Q.front();Q.pop();
			Re x=now.x,y=now.y;vis[x][y]=0;
			for(Re o=0;o<4;++o){
				Re nx=x+wx[o],ny=y+wy[o];
				if(nx<1||nx>n||ny<1||ny>m)continue;
				if(dp[nx][ny][s]>dp[x][y][s]+B[nx][ny]){
					dp[nx][ny][s]=dp[x][y][s]+B[nx][ny],pre[nx][ny][s]=PRE(x,y,s);
					if(!vis[nx][ny])Q.push(QAQ(nx,ny)),vis[nx][ny]=1;
				}
			}
		}
	}
	int Ans[N][N];
	inline void dfs(Re i,Re j,Re s){
		Ans[i][j]=1;PRE to=pre[i][j][s];
		if(to.s){
			dfs(to.i,to.j,to.s);
			if(to.i==i&&to.j==j)dfs(to.i,to.j,s^to.s);
		}
	}
	inline void sakura(){
		memset(dp,63,sizeof(dp));
		Re V=(1<<ct)-1,inf=dp[0][0][0];
		for(Re i=1;i<=n;++i)
			for(Re j=1;j<=m;++j)
				if(A[i][j])dp[i][j][1<<A[i][j]-1]=0;
		for(Re s=0;s<=V;++s){
			for(Re i=1;i<=n;++i)
				for(Re j=1;j<=m;++j){
					for(Re t=(s-1)&s,tmp;t;t=(t-1)&s)
						if((tmp=dp[i][j][t]+dp[i][j][s^t]-B[i][j])<dp[i][j][s])
							dp[i][j][s]=tmp,pre[i][j][s]=PRE(i,j,t);
					if(dp[i][j][s]!=inf)Q.push(QAQ(i,j)),vis[i][j]=1;
				}
			SPFA(s);
		}
		Re ans=2e9,x,y;
		for(Re i=1;i<=n;++i)
			for(Re j=1;j<=m;++j)
				if(A[i][j])ans=dp[x=i][y=j][V];
		printf("%d\n",ans);
		dfs(x,y,V);
		for(Re i=1;i<=n;puts(""),++i)
			for(Re j=1;j<=m;++j)
				putchar(A[i][j]?'x':(Ans[i][j]?'o':'_'));
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m);
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=m;++j){
			in(B[i][j]);
			if(!B[i][j])A[i][j]=++ct;
		}
	T1.sakura();
}
