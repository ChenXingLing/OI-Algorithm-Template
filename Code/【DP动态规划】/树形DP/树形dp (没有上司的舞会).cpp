#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=6003;
int x,y,o,n,A[N],fa[N],head[N],f[N][2];
struct QAQ{int next,to;}a[N];
inline void add(int x,int y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void dfs(int x){
    f[x][1]=A[x];
	for(Re i=head[x],to;i;i=a[i].next){
        dfs(to=a[i].to);
        f[x][0]+=max(f[to][0],f[to][1]);
        f[x][1]+=f[to][0];
    }
}
int main(){
    scanf("%d",&n);
    for(Re i=1;i<=n;i++)scanf("%d",&A[i]);
    for(Re i=1;i<n;i++)scanf("%d%d",&x,&y),fa[x]=y,add(y,x);
    for(Re i=1;i<=n;i++)
        if(!fa[i]){
            dfs(i);
            printf("%d\n",max(f[i][0],f[i][1]));
            return 0;
        }
}
