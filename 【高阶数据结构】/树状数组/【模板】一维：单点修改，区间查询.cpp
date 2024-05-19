#include<cstdio>
#define LL long long
#define Re register int
const int N=5e5+3;
int n,x,y,T,op;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct BIT{
    LL C[N];
    inline void add(Re x,Re v){while(x<=n)C[x]+=v,x+=x&-x;}
    inline LL ask(Re x){LL ans=0;while(x)ans+=C[x],x-=x&-x;return ans;}
    inline LL ask(Re L,Re R){return ask(R)-ask(L-1);}
}TR;
int main(){
    in(n),in(T);
    for(Re i=1;i<=n;++i)in(x),TR.add(i,x);
    while(T--){
        in(op),in(x),in(y);
        if(op<2)TR.add(x,y);
        else printf("%ld\n",TR.ask(x,y));
    }
}
