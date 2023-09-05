#include<algorithm>
#include<cstring>
#include<cstdio>
#define R register int
using namespace std;
int n,b,c,d,t,longson[10005],d1[10005],d2[10005],df[10005],head[10005];
struct QAQ{int to,next,w;}a[20005];
inline void add(int x,int y,int w){a[++t].to=y,a[t].w=w,a[t].next=head[x],head[x]=t;}
inline void dfs(int x,int pa){//横冲直撞正向搜索 
	for(R i=head[x];i;i=a[i].next){// oooO ↘┏━┓ ↙ Oooo 
		R s,to=a[i].to;//            ( 踩)→┃你┃ ←(死 ) 
		if(to==pa)continue;//        \ ( →┃√┃ ← ) / 
		dfs(to,x);s=d1[to]+a[i].w;// \_)↗┗━┛ ↖(_/ 
		if(s>d1[x])d2[x]=d1[x],d1[x]=s,longson[x]=to;//记录最长路径所踩到头的儿子 
		else d2[x]=max(d2[x],s);
	}
}
inline void dfsf(int x,int pa){//倒立螺旋反向搜索 
	for(R i=head[x];i;i=a[i].next){
		R to=a[i].to;
		if(to==pa)continue;
		if(longson[x]==to)df[to]=a[i].w+max(d2[x],df[x]);
//如果踩过这个儿子的头有一条最长路，那么该儿子的反向最大可能是这位父亲的次大或继续反向取最大  
		else df[to]=a[i].w+max(d1[x],df[x]);
//如果最长路没踩他的头，那么他的反向最大是父亲的最大或继续反向取最大 
		dfsf(to,x);
	}
}
inline int sakura(){
	while(~scanf("%d",&n)){
		memset(longson,0,sizeof(longson));
		memset(head,0,sizeof(head));
		memset(d1,0,sizeof(d1));
		memset(d2,0,sizeof(d2));
		memset(df,0,sizeof(df));
		memset(a,0,sizeof(a));t=0;
		for(R i=2;i<=n;i++){
			scanf("%d%d",&b,&c);
			add(i,b,c),add(b,i,c);
		}
		dfs(1,0);dfsf(1,0);
		for(R i=1;i<=n;i++)printf("%d\n",max(d1[i],df[i]));
	}
	return 0;
}
int QAQWQ=sakura();
int main(){}
