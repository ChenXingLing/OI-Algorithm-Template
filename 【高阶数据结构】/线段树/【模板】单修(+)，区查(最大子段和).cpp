#include<algorithm>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=5e4+3;
int n,x,y,T,op,A[N];
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
    struct QAQ{LL S,max,lmax,rmax;}tr[N<<2];
    inline void pushup(QAQ &A,const QAQ &L,const QAQ &R){
        A.S=L.S+R.S;
        A.lmax=max(L.lmax,L.S+R.lmax);
        A.rmax=max(R.rmax,R.S+L.rmax);
        A.max=max(max(max(L.max,R.max),max(A.lmax,A.rmax)),L.rmax+R.lmax);
    }
    inline void change(Re p,Re L,Re R,Re x,Re v){
        if(L==R){tr[p].S=tr[p].max=tr[p].lmax=tr[p].rmax=v;return;}
        if(x<=mid)change(pl,L,mid,x,v);
        else change(pr,mid+1,R,x,v);
        pushup(tr[p],tr[pl],tr[pr]);
    }
    inline QAQ ask(Re p,Re L,Re R,Re l,Re r){
        if(l<=L&&R<=r)return tr[p];
        if(r<=mid)return ask(pl,L,mid,l,r);
        else if(l>mid)return ask(pr,mid+1,R,l,r);
        else{QAQ ans;pushup(ans,ask(pl,L,mid,l,r),ask(pr,mid+1,R,l,r));return ans;}
    }
}TR;
int main(){
    in(n);
    for(Re i=1;i<=n;++i)in(A[i]),TR.change(1,1,n,i,A[i]);
    in(T);
    while(T--){
        in(op),in(x),in(y);
        if(op)printf("%lld\n",TR.ask(1,1,n,x,y).max);
        else TR.change(1,1,n,x,y);
    }
}
