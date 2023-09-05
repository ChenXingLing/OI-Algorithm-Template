#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=1e4+3,M=3e5+3;
int n,m,x,y,o,head[N];
struct QAQ{int w,to,next;}a[N<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
struct Tree_Diam_DFS{
	int cur,dis[N];
	inline void dfs(Re x,Re fa){
		if(dis[x]>dis[cur])cur=x;
		for(Re i=head[x],to;i;i=a[i].next)
			if((to=a[i].to)!=fa)dis[to]=dis[x]+a[i].w,dfs(to,x);
	}
	inline int sakura(){
		dfs(1,0);
		memset(dis,0,sizeof(dis));
		dfs(cur,0);
		return dis[cur];
	}
}T1;
int main(){
	in(n),m=n-1;
    while(m--)in(x),in(y),add(x,y,1),add(y,x,1);
    printf("%d\n",T1.sakura());
}
