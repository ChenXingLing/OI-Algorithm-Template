#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=5003,P=998244353;
int n,m,o,x,y,f[N],g[N],A[N],jc[N],head[N];char s[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int mi(Re x,Re k){
	Re s=1;
	while(k){
		if(k&1)s=(LL)s*x%P;
		x=(LL)x*x%P,k>>=1;
	}
	return s;
}
inline int inv(Re x){return mi(x,P-2);}
int sz1[N],sz0[N],lim[N],dp[N][N],tmp[N];
inline void dfs0(Re x,Re fa){
	sz0[x]=(!A[x]),sz1[x]=A[x];
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa)dfs0(to,x),sz1[x]+=sz1[to],sz0[x]+=sz0[to];
//	lim[x]=min(sz1[x],size[x]-sz1[x]);
}
inline void dfs(Re x,Re fa){
	dp[x][0]=1;
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=fa){
			dfs(to,x);
			for(Re j=0;j<=lim[x]+lim[to];++j)tmp[j]=0;
			for(Re j=lim[x];j>=0;--j)
				for(Re k=lim[to];k>=0;--k)
					(tmp[j+k]+=(LL)dp[x][j]*dp[to][k]%P)%=P;
			lim[x]+=lim[to];
			for(Re j=0;j<=lim[x];++j)dp[x][j]=tmp[j];
		}
	++lim[x];
	if(A[x])for(Re j=min(lim[x],sz0[x]);j>=1;--j)
		(dp[x][j]+=(LL)dp[x][j-1]*(sz0[x]-(j-1))%P)%=P;
	else for(Re j=min(lim[x],sz1[x]);j>=1;--j)
		(dp[x][j]+=(LL)dp[x][j-1]*(sz1[x]-(j-1))%P)%=P;
	while(!dp[x][lim[x]])--lim[x];
}
inline int C(Re m,Re n){return (LL)jc[n]*inv(jc[m])%P*inv(jc[n-m])%P;}
int main(){
//	freopen("match.in","r",stdin);
//	freopen("match.out","w",stdout);
	in(n),scanf("%s",s+1),m=n-1,jc[0]=1;
	for(Re i=1;i<=n;++i)A[i]=s[i]-'0',jc[i]=(LL)jc[i-1]*i%P;
	while(m--)in(x),in(y),add(x,y),add(y,x);
	dfs0(1,0),dfs(1,0);
//	for(Re i=1;i<=n;++i)printf("lim[%d]=%d\n",i,lim[i]);
//	for(Re i=0;i<=n/2;++i)printf("dp[%d]=%d\n",i,dp[1][i]);
//	for(Re j=0;j<=lim[1];++j)printf("%d ",dp[1][j]);
	for(Re j=0;j<=lim[1];++j)g[j]=(LL)dp[1][j]*jc[n/2-j]%P;
	for(Re i=lim[1];i>=0;--i){
		f[i]=g[i];
		for(Re j=i+1;j<=lim[1];++j)f[i]=(f[i]-(LL)C(i,j)*f[j]%P+P)%P;
	}
	for(Re i=0;i<=n/2;++i)printf("%d\n",f[i]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
