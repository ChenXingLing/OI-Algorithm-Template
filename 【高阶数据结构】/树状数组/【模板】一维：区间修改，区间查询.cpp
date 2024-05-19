/*
            n        n
S[x]= (x+1)*¡ÆA[i] - ¡Æi*A[i]
           i=1      i=1
*/
#include<cstdio>
#define LL long long
#define Re register int
const int N=1e6+3;
int n,x,y,z,T,op;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct BIT{
    LL C1[N],C2[N];
    inline void add(Re x,Re v){Re i=x;while(i<=n)C1[i]+=v,C2[i]+=(LL)x*v,i+=i&-i;}
    inline void add(Re L,Re R,Re v){add(L,v),add(R+1,-v);}
    inline LL ask(Re x){Re i=x;LL ans=0;while(i)ans+=(x+1)*C1[i]-C2[i],i-=i&-i;return ans;}
    inline LL ask(Re L,Re R){return ask(R)-ask(L-1);}
}TR;
int main(){
    in(n),in(T);
    for(Re i=1;i<=n;++i)in(x),TR.add(i,i,x);
    while(T--){
        in(op),in(x),in(y);
        if(op<2)in(z),TR.add(x,y,z);
        else printf("%lld\n",TR.ask(x,y));
    }
}
