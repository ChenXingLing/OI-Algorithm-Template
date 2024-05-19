#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register LL
using namespace std;
const LL N=2e4+3,M=2e5+3,inf=2e18,logN=14;
LL n,m,o,x,y,T,A[N],head[N];
struct QAQ{LL to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct JI{
    LL p[61];JI(){memset(p,0,sizeof(p));}
    inline void insert(Re x){
        for(Re i=60;i>=0;--i)
            if((x>>i)&1){
                if(!p[i]){p[i]=x;break;}
                x^=p[i];
            }
    }
    inline void merge(JI O){
        for(Re i=60;i>=0;--i)if(O.p[i])insert(O.p[i]);
    }
    inline LL ask(){
        Re ans=0;
        for(Re i=60;i>=0;--i)ans=max(ans,ans^p[i]);
        return ans;
    }
};
struct LCA{
    LL deep[N],fa[N][15],ant[N][15];JI dp[N][15];
    inline void dfs(Re x,Re fa){
        deep[x]=deep[ant[x][0]=fa]+1,dp[x][0].insert(A[fa]);
        for(Re j=1;(1<<j)<=deep[x];++j)ant[x][j]=ant[ant[x][j-1]][j-1],dp[x][j]=dp[x][j-1],dp[x][j].merge(dp[ant[x][j-1]][j-1]);
        for(Re i=head[x];i;i=a[i].next)if(a[i].to!=fa)dfs(a[i].to,x);
    }
    inline JI ask(Re x,Re y){
        JI Ans;Ans.insert(A[x]),Ans.insert(A[y]);
        if(deep[x]<deep[y])swap(x,y);
        for(Re i=logN;i>=0;--i)if(deep[ant[x][i]]>=deep[y])Ans.merge(dp[x][i]),x=ant[x][i];
        if(x==y)return Ans;
        for(Re i=logN;i>=0;--i)if(ant[x][i]!=ant[y][i])Ans.merge(dp[x][i]),Ans.merge(dp[y][i]),x=ant[x][i],y=ant[y][i];
        Ans.merge(dp[x][0]);
        return Ans;
    }
}T1;
int main(){
//    freopen("lucky.in","r",stdin);
//    freopen("lucky.out","w",stdout);
    in(n),in(T),m=n-1;
    for(Re i=1;i<=n;++i)in(A[i]);
    while(m--)in(x),in(y),add(x,y),add(y,x);
    T1.dfs(1,0);
    while(T--)in(x),in(y),printf("%lld\n",T1.ask(x,y).ask());
}
