#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
const int N=1e5+3,M=2e5+3;
int n,m,x,y,m_,op;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Euler_Circle__Undirected_Graph{//无向图欧拉回路
	int o,du[N],cur[N],ans[M],pan[M<<1],head[N];
	struct QAQ{int to,next;}a[M<<1];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void dfs(Re x){
		for(Re i=head[x];i;i=head[x]){
			head[x]=a[i].next;//当前弧优化
			if(!pan[i]){
				pan[i]=pan[i^1]=1;
				dfs(a[i].to);
				ans[++ans[0]]=(i&1)?-i/2:i/2;//正数表示 x->y，负数表示y->x 
			}
		}
	}
	inline void sakura(){
		in(n),in(m),m_=m,o=1;
		while(m_--)in(x),in(y),add(x,y),add(y,x),++du[x],++du[y];
		for(Re i=1;i<=n;cur[i]=head[i],++i)if(du[i]&1){puts("NO");return;}//无向图点度数必须为偶数
		for(Re i=1;i<=n;++i)if(du[i]){dfs(i);break;}//任意找一个有度数的起点
		if(ans[0]!=m){puts("NO");return;}//跑不满m条边
		puts("YES");
		for(Re i=ans[0];i>=1;--i)printf("%d ",ans[i]);
	}
}T1;
struct Euler_Circle__Directed_Graph{//有向图欧拉回路
	int o,ru[N],chu[N],cur[N],ans[M],head[N];
	struct QAQ{int to,next;}a[M<<1];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void dfs(Re x){
		for(Re i=head[x];i;i=head[x]){
			head[x]=a[i].next;//当前弧优化
			dfs(a[i].to);
			ans[++ans[0]]=i;
		}
	}
	inline void sakura(){
		in(n),in(m),m_=m;
		while(m_--)in(x),in(y),add(x,y),++ru[y],++chu[x];
		for(Re i=1;i<=n;cur[i]=head[i],++i)if(ru[i]!=chu[i]){puts("NO");return;}//有向图点入度必须等于出度
		for(Re i=1;i<=n;++i)if(chu[i]){dfs(i);break;}//任意找一个有出度的起点
		if(ans[0]!=m){puts("NO");return;}//跑不满m条边
		puts("YES");
		for(Re i=ans[0];i>=1;--i)printf("%d ",ans[i]);
	}
}T2;
int main(){
	in(op);
	if(op==1)T1.sakura();//无向图 
	if(op==2)T2.sakura();//有向图 
}
