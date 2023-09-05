#include<algorithm>
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
#define div(a,b) floor((double)a/b)
using namespace std;
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
    struct QAQ{LL S,add,min,max;}tr[N<<2];
    inline void pushup(Re p){
        tr[p].S=tr[pl].S+tr[pr].S;
        tr[p].min=min(tr[pl].min,tr[pr].min);
        tr[p].max=max(tr[pl].max,tr[pr].max);
    }
    inline void updata(Re p,Re L,Re R,LL v){tr[p].S+=v*(R-L+1),tr[p].add+=v,tr[p].min+=v,tr[p].max+=v;}
    inline void pushdown(Re p,Re L,Re R){
        if(tr[p].add)updata(pl,L,mid,tr[p].add),updata(pr,mid+1,R,tr[p].add),tr[p].add=0;
    }
    inline void build(Re p,Re L,Re R){
        if(L==R){tr[p].S=tr[p].min=tr[p].max=A[L];return;}
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
    inline void change_div(Re p,Re L,Re R,Re l,Re r,Re v){
        if(l<=L&&R<=r&&(div(tr[p].max,v)-tr[p].max==div(tr[p].min,v)-tr[p].min)){
            updata(p,L,R,div(tr[p].max,v)-tr[p].max);return;
        }
        pushdown(p,L,R);
        if(l<=mid)change_div(pl,L,mid,l,r,v);
        if(r>mid)change_div(pr,mid+1,R,l,r,v);
        pushup(p);
    }
    inline LL ask_min(Re p,Re L,Re R,Re l,Re r){
        if(l<=L&&R<=r)return tr[p].min;
        LL ans=1e18;pushdown(p,L,R);
        if(l<=mid)ans=min(ans,ask_min(pl,L,mid,l,r));
        if(r>mid)ans=min(ans,ask_min(pr,mid+1,R,l,r));
        return ans;
    }
    inline LL ask_S(Re p,Re L,Re R,Re l,Re r){
        if(l<=L&&R<=r)return tr[p].S;
        LL ans=0;pushdown(p,L,R);
        if(l<=mid)ans+=ask_S(pl,L,mid,l,r);
        if(r>mid)ans+=ask_S(pr,mid+1,R,l,r);
        return ans;
    }
}TR;
int main(){
    in(n),in(T);
    for(Re i=1;i<=n;++i)in(A[i]);
    TR.build(1,1,n);
    while(T--){
        in(op),in(x),in(y),++x,++y;
        if(op<2)in(z),TR.change(1,1,n,x,y,z);
        else if(op<3)in(z),TR.change_div(1,1,n,x,y,z);
        else if(op<4)printf("%lld\n",TR.ask_min(1,1,n,x,y));
        else printf("%lld\n",TR.ask_S(1,1,n,x,y));
    }
}
