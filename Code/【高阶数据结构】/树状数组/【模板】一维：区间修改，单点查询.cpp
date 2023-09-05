#include<cstdio>
#define LL long long
#define Re register int
const int N=5e5+3;
int n,x,y,z,T,op;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct BIT{
    LL C[N];
    inline void add(Re x,Re v){while(x<=n)C[x]+=v,x+=x&-x;}
    inline void add(Re L,Re R,Re v){add(L,v),add(R+1,-v);}
    inline LL ask(Re x){LL ans=0;while(x)ans+=C[x],x-=x&-x;return ans;}
}TR;
int main(){
    in(n),in(T);
    for(Re i=1;i<=n;++i)in(x),TR.add(i,i,x);
    while(T--){
        in(op),in(x);
        if(op<2)in(y),in(z),TR.add(x,y,z);
        else printf("%lld\n",TR.ask(x));
    }
}
