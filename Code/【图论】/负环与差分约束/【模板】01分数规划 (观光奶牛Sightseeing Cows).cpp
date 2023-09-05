#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=1e4+5,M=5e5+5,inf=2e9;
int x,y,z,n,m,o,T,to,A[N],cha[N],pan[N],head[N];double dis[N];
struct QAQ{int w,to,next;}a[M<<1];queue<int>Q;
inline void in(Re &x){
    Re fu=0;x=0;char ch=getchar();
    while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=fu?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].to=y,a[o].w=z,a[o].next=head[x],head[x]=o;}
inline int SPFA(Re st,double mid){
    for(Re i=0;i<=n;++i)dis[i]=-inf,pan[i]=cha[i]=0;
    dis[st]=0,cha[st]=pan[st]=1,Q.push(st);
    while(!Q.empty()){
        x=Q.front(),Q.pop();
        pan[x]=0;
        for(Re i=head[x];i;i=a[i].next)
            if(dis[to=a[i].to]<dis[x]+A[x]-mid*a[i].w){
                dis[to]=dis[x]+A[x]-mid*a[i].w;
                if(++cha[to]>n)return 1;
                if(!pan[to])Q.push(to);
            }
    }
    return 0;
}
int main(){
    in(n),in(m);
    for(Re i=1;i<=n;++i)in(A[i]);
    while(m--)in(x),in(y),in(z),add(x,y,z);
    double l=0,r=1000000,mid;
    while(r-l>1e-4){
        mid=(l+r)/2;
        if(SPFA(1,mid))l=mid;
        else r=mid;
    }
    printf("%.2lf",l);
}
