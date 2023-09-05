#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=5e5+3,M=5e5+3,logN=18;//注意考虑最多一次跳\floor(\log N)级
int T,Q,n,m,x,y,o,root,head[N];
struct QAQ{int to,next;}a[M<<1];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct LCA{
	int deep[N],ant[N][logN+1];
	inline void dfs(Re x,Re fa){
		deep[x]=deep[ant[x][0]=fa]+1;
		for(Re i=1;(1<<i)<=deep[x];++i)ant[x][i]=ant[ant[x][i-1]][i-1];
		for(Re i=head[x];i;i=a[i].next)if(a[i].to!=fa)dfs(a[i].to,x);
	}
	inline int lca(Re x,Re y){
		if(deep[x]<deep[y])swap(x,y);//先把x变为深度更大的点
		for(Re i=logN;i>=0;--i)if(deep[ant[x][i]]>=deep[y])x=ant[x][i];//x单独往上跳到深度与y相等的位置
		if(x==y)return x;//如果已经相遇了就返回
		for(Re i=logN;i>=0;--i)if(ant[x][i]!=ant[y][i])x=ant[x][i],y=ant[y][i];//如果往上跳2^i步都还没有相遇
		return ant[x][0];//最后一步到达
	}
}T1;
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
int main(){
	in(n),in(Q),in(root),m=n-1;
	while(m--)in(x),in(y),add(x,y),add(y,x);
	T1.dfs(root,0);
	while(Q--)in(x),in(y),printf("%d\n",T1.lca(x,y));
}
