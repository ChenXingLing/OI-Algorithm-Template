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
struct Tree_Diam_DP1{
	int ans,dis[N];
	inline void dfs(Re x,Re fa){
		for(Re i=head[x],to,tmp;i;i=a[i].next)
			if((to=a[i].to)!=fa){
				dfs(to,x);
				ans=max(ans,dis[x]+dis[to]+a[i].w);
				dis[x]=max(dis[x],dis[to]+a[i].w);
			}
	}
	inline int sakura(){dfs(1,0);return ans;}
}T1;
struct Tree_Diam_DP2{
	int ans,dis[N][2];
	inline void dfs(Re x,Re fa){
		for(Re i=head[x],to,tmp;i;i=a[i].next)
			if((to=a[i].to)!=fa){
				dfs(to,x);
				if(dis[x][0]<(tmp=dis[to][0]+a[i].w))dis[x][1]=dis[x][0],dis[x][0]=tmp;
				else dis[x][1]=max(dis[x][1],tmp);
			}
		ans=max(ans,dis[x][1]+dis[x][0]);
	}
	inline int sakura(){dfs(1,0);return ans;}
}T2;
int main(){
	in(n),m=n-1;
    while(m--)in(x),in(y),add(x,y,1),add(y,x,1);
    printf("%d\n",T1.sakura());
//    printf("%d\n",T2.sakura());
}
