#include<algorithm>
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int n,x,y,z,T,op;LL A[N];
template<typename T>inline void in(T &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Segment_Tree{
    #define pl (p<<1)
    #define pr (p<<1|1)
    #define mid ((L+R)>>1)
    struct QAQ{LL S,max;}tr[N<<2];
    inline void pushup(Re p){
        tr[p].S=tr[pl].S+tr[pr].S;
        tr[p].max=max(tr[pl].max,tr[pr].max);
    }
    inline void build(Re p,Re L,Re R){
        if(L==R){tr[p].S=tr[p].max=A[L];return;}
        build(pl,L,mid),build(pr,mid+1,R);
        pushup(p);
    }
    inline void change(Re p,Re L,Re R,Re l,Re r){
        if(tr[p].max<=1)return;
        if(L==R){tr[p].max=tr[p].S=sqrt(tr[p].S);return;}
        if(l<=mid)change(pl,L,mid,l,r);
        if(r>mid)change(pr,mid+1,R,l,r);
        pushup(p);
    }
    inline LL ask(Re p,Re L,Re R,Re l,Re r){
        if(l<=L&&R<=r)return tr[p].S;
        LL ans=0;
        if(l<=mid)ans+=ask(pl,L,mid,l,r);
        if(r>mid)ans+=ask(pr,mid+1,R,l,r);
        return ans;
    }
}TR;
int main(){
    in(n);
    for(Re i=1;i<=n;++i)in(A[i]);
    TR.build(1,1,n),in(T);
    while(T--){
        in(op),in(x),in(y);if(x>y)swap(x,y);
        if(op)printf("%lld\n",TR.ask(1,1,n,x,y));
        else TR.change(1,1,n,x,y);
    }
}
