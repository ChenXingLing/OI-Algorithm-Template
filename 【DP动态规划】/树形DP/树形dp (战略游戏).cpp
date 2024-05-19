#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=1503;
int x,y,o,n,m,head[N],f[N][2];
struct QAQ{int next,to;}a[N<<1];
inline void add(int x,int y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void dfs(int x,int Fa){
    f[x][0]=0,f[x][1]=1;
	for(Re i=head[x],to;i;i=a[i].next)
		if((to=a[i].to)!=Fa){
        	dfs(to,x);
        	f[x][1]+=min(f[to][0],f[to][1]);
        	f[x][0]+=f[to][1];
    	}
}
int main(){
    scanf("%d",&n);
    for(Re i=1;i<=n;i++){
		scanf("%d%d",&x,&m);
    	while(m--)scanf("%d",&y),add(x,y),add(y,x);
	}
	dfs(0,-1);
	printf("%d",min(f[0][0],f[0][1]));
}
