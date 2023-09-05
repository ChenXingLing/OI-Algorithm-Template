#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=303;
int x,n,o,K,root=0,A[N],size[N],head[N],f[N][N];
struct QAQ{int to,next;}a[N];
inline void add(int x,int y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void dfs(int x){
	if(x!=root)f[x][1]=A[x];//非根节点必须选自己
	else f[x][0]=0;//根节点自己不能选
	size[x]=1;
	for(int i=head[x],to;i;i=a[i].next){
        dfs(to=a[i].to),size[x]+=size[to];
        for(int j=size[x];j;j--)
            for(int k=min(j,size[to]);k>=0;k--)
                f[x][j]=max(f[x][j],f[x][j-k]+f[to][k]);
    }
    if(x!=root)f[x][0]=0;//整个子树都不选的情况
}
int main(){
    scanf("%d%d",&n,&K);
    memset(f,-63,sizeof(f));
    for(int i=1;i<=n;i++)scanf("%d%d",&x,&A[i]),add(x,i);
    dfs(root);
    printf("%d",f[root][K]);
    return 0;
}
