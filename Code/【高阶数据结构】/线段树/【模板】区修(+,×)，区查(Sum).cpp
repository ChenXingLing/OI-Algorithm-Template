#include<cstdio>
#define LL long long
#define Re register int
const int N=1e5+3;
int n,x,y,z,T,P,op,A[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Segment_Tree{
    #define pl (p<<1)
    #define pr (p<<1|1)
    #define mid ((L+R)>>1)
    struct QAQ{LL S,mul,add;}tr[N<<2];
    inline void pushup(Re p){tr[p].S=(tr[pl].S+tr[pr].S)%P;}
    inline void updata1(Re p,LL v){
        tr[p].S=(LL)tr[p].S*v%P,tr[p].mul=(LL)tr[p].mul*v%P,tr[p].add=(LL)tr[p].add*v%P;
    }
    inline void updata2(Re p,Re L,Re R,LL v){(tr[p].S+=v*(R-L+1)%P)%=P,(tr[p].add+=v)%=P;}
    inline void pushdown(Re p,Re L,Re R){
        if(tr[p].mul!=1)updata1(pl,tr[p].mul),updata1(pr,tr[p].mul),tr[p].mul=1;
        if(tr[p].add)updata2(pl,L,mid,tr[p].add),updata2(pr,mid+1,R,tr[p].add),tr[p].add=0;
    }
    inline void build(Re p,Re L,Re R){
        tr[p].mul=1;
        if(L==R){tr[p].S=A[L]%P;return;}
        build(pl,L,mid),build(pr,mid+1,R);
        pushup(p);
    }
    inline void change(Re p,Re L,Re R,Re l,Re r,Re v,Re op){
        if(l<=L&&R<=r){if(op<2)updata1(p,v);else updata2(p,L,R,v);return;}
        pushdown(p,L,R);
        if(l<=mid)change(pl,L,mid,l,r,v,op);
        if(r>mid)change(pr,mid+1,R,l,r,v,op);
        pushup(p);
    }
    inline LL ask(Re p,Re L,Re R,Re l,Re r){
        if(l<=L&&R<=r)return tr[p].S;
        LL ans=0;pushdown(p,L,R);
        if(l<=mid)(ans+=ask(pl,L,mid,l,r))%=P;
        if(r>mid)(ans+=ask(pr,mid+1,R,l,r))%=P;
        return ans;
    }
}TR;
int main(){
    in(n),in(T),in(P);
    for(Re i=1;i<=n;++i)in(A[i]);
    TR.build(1,1,n);
    while(T--){
        in(op),in(x),in(y);
        if(op<3)in(z),TR.change(1,1,n,x,y,z,op);
        else printf("%lld\n",TR.ask(1,1,n,x,y));
    }
}
