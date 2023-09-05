#include<cstdio>
#define LL long long
#define Re register int
const int N=5e5+3;
int n,x,y,T;LL z,A[N];char op;
template<typename T>inline void in(T &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline LL abs(LL a){return a<0?-a:a;}
inline LL gcd(LL a,LL b){return !b?a:gcd(b,a%b);}
struct BIT{
    LL C[N];
    inline void add(Re x,LL v){while(x<=n)C[x]+=v,x+=x&-x;}
    inline void add(Re L,Re R,LL v){add(L,v),add(R+1,-v);}
    inline LL ask(Re x){LL ans=0;while(x)ans+=C[x],x-=x&-x;return ans;}
}TR0;
struct Segment_Tree{
    #define pl (p<<1)
    #define pr (p<<1|1)
    #define mid ((L+R)>>1)
    LL tr[N<<2];
    inline void pushup(Re p){tr[p]=gcd(tr[pl],tr[pr]);}
    inline void build(Re p,Re L,Re R){
        if(L==R){tr[p]=A[L]-A[L-1];return;}
        build(pl,L,mid),build(pr,mid+1,R);
        pushup(p);
    }
    inline void change(Re p,Re L,Re R,Re x,LL v){
        if(L==R){tr[p]+=v;return;}
        if(x<=mid)change(pl,L,mid,x,v);
        else change(pr,mid+1,R,x,v);
        pushup(p);
    }
    inline LL ask(Re p,Re L,Re R,Re l,Re r){
        if(l<=L&&R<=r)return abs(tr[p]);
        if(r<=mid)return ask(pl,L,mid,l,r);
        else if(l>mid)return ask(pr,mid+1,R,l,r);
        else return gcd(ask(pl,L,mid,l,r),ask(pr,mid+1,R,l,r));
    }
}TR;
int main(){
    in(n),in(T);
    for(Re i=1;i<=n;++i)in(A[i]),TR0.add(i,i,A[i]);
    TR.build(1,1,n);
    while(T--){
        scanf(" %c",&op),in(x),in(y);
        if(op=='Q')printf("%lld\n",gcd(TR0.ask(x),TR.ask(1,1,n,x+1,y)));
        else{
            in(z),TR0.add(x,y,z),TR.change(1,1,n,x,z);if(y<n)TR.change(1,1,n,y+1,-z);
        }
    }
}
