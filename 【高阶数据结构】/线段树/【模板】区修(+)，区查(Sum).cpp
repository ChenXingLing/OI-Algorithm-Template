#include<cstdio>
#define LL long long
#define Re register int
const int N=1e5+3;
int n,x,y,z,T,op,A[N];
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
    struct QAQ{LL S,add;}tr[N<<2];
    inline void pushup(Re p){tr[p].S=tr[pl].S+tr[pr].S;}
    inline void updata(Re p,Re L,Re R,LL v){tr[p].S+=v*(R-L+1),tr[p].add+=v;}
    inline void pushdown(Re p,Re L,Re R){
        if(tr[p].add)updata(pl,L,mid,tr[p].add),updata(pr,mid+1,R,tr[p].add),tr[p].add=0;
    }
    inline void build(Re p,Re L,Re R){
        if(L==R){tr[p].S=A[L];return;}
        build(pl,L,mid),build(pr,mid+1,R);
        pushup(p);
    }
    inline void change(Re p,Re L,Re R,Re l,Re r,Re v){
        if(l<=L&&R<=r){updata(p,L,R,v);return;}
        pushdown(p,L,R);
        if(l<=mid)change(pl,L,mid,l,r,v);
        if(r>mid)change(pr,mid+1,R,l,r,v);
        pushup(p);
    }
    inline LL ask(Re p,Re L,Re R,Re l,Re r){
        if(l<=L&&R<=r)return tr[p].S;
        LL ans=0;pushdown(p,L,R);
        if(l<=mid)ans+=ask(pl,L,mid,l,r);
        if(r>mid)ans+=ask(pr,mid+1,R,l,r);
        return ans;
    }
}TR;
int main(){
    in(n),in(T);
    for(Re i=1;i<=n;++i)in(A[i]);
    TR.build(1,1,n);
    while(T--){
        in(op),in(x),in(y);
        if(op<2)in(z),TR.change(1,1,n,x,y,z);
        else printf("%lld\n",TR.ask(1,1,n,x,y));
    }
}
