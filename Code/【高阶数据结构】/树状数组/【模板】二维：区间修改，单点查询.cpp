#include<cstdio>
#define y1 yyyy
#define LL long long
#define Re register int
const int N=4096+3;
int n,m,T,x,x1,y1,x2,y2,op;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct BIT{
    LL C[N][N];
    inline void add(Re x,Re y,Re v){
        while(x<=n){Re j=y;while(j<=m)C[x][j]+=v,j+=j&-j;x+=x&-x;}
    }
    inline void add(Re x1,Re y1,Re x2,Re y2,Re z){
        add(x1,y1,z),add(x1,y2+1,-z),add(x2+1,y1,-z),add(x2+1,y2+1,z);
    }
    inline LL ask(Re x,Re y){
        LL ans=0;
        while(x){Re j=y;while(j)ans+=C[x][j],j-=j&-j;x-=x&-x;}
        return ans;
    }
}TR;
int main(){
    in(n),in(m);
    while(~scanf("%d",&op)){
        in(x1),in(y1);
        if(op<2)in(x2),in(y2),in(x),TR.add(x1,y1,x2,y2,x);
        else printf("%lld\n",TR.ask(x1,y1));
    }
}
