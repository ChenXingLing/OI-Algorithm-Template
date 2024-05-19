#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=5e5+3,logN=19;
int n,m,o,x,y,T,rt,head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct LCA{
	int O,lg[N<<1],Qx[N<<1],Qd[N<<1],fir[N],deep[N],f[N<<1][logN+1],ans[N<<1][logN+1];
	inline void dfs(Re x,Re fa){
		Qx[fir[x]=++O]=x,Qd[O]=deep[x]=deep[fa]+1;//加x加入欧拉序列
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=fa)dfs(to,x),Qx[++O]=x,Qd[O]=deep[x];//加x加入欧拉序列
	}
	inline void build(Re rt){
		dfs(rt,0),lg[0]=-1;
		for(Re i=1;i<=O;++i)f[i][0]=Qd[i],ans[i][0]=Qx[i],lg[i]=lg[i>>1]+1;
		for(Re j=1;j<=logN;++j)
			for(Re i=1;i+(1<<j)-1<=O;++i)
				if(f[i][j-1]<f[i+(1<<j-1)][j-1])f[i][j]=f[i][j-1],ans[i][j]=ans[i][j-1];
				else f[i][j]=f[i+(1<<j-1)][j-1],ans[i][j]=ans[i+(1<<j-1)][j-1];
	}
	inline int lca(Re x,Re y){
		Re L=fir[x],R=fir[y];
		if(L>R)swap(L,R);
		Re m=lg[R-L+1];
		return f[L][m]<f[R-(1<<m)+1][m]?ans[L][m]:ans[R-(1<<m)+1][m];
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),in(rt),m=n-1;
	while(m--)in(x),in(y),add(x,y),add(y,x);
	T1.build(rt);
	while(T--)in(x),in(y),printf("%d\n",T1.lca(x,y));
}
