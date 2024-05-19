#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=2003,M=3e5+3,inf=2e9;
int n,m,x,y,z,o,T,pan[N],chu[N],dis[N],head[N];queue<int>Q;
struct QAQ{int w,to,next;}a[M<<1];
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int SPFA(Re st){
    for(Re i=1;i<=n;++i)dis[i]=inf,chu[i]=pan[i]=0;
    while(!Q.empty())Q.pop();
    Q.push(st),dis[st]=0,chu[st]=0,pan[st]=1;
    while(!Q.empty()){
        Re x=Q.front();Q.pop();pan[x]=0;
        for(Re i=head[x],to;i;i=a[i].next)
            if(dis[to=a[i].to]>dis[x]+a[i].w){
                dis[to]=dis[x]+a[i].w;
                if((chu[to]=chu[x]+1)>=n)return 1;
//                if(++chu[to]>=n)return 1;
                if(!pan[to])pan[to]=1,Q.push(to);
            }
    }
    return 0;
}
int main(){
    in(T);
    while(T--){
        in(n),in(m),memset(head,0,sizeof(head)),o=0;
        while(m--){in(x),in(y),in(z),add(x,y,z);if(z>=0)add(y,x,z);}
        puts(SPFA(1)?"YES":"NO");
    }
}
