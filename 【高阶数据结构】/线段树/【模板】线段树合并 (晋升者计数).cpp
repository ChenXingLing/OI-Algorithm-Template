#include<algorithm>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,logN=17;
int n,m,x,o,T,op,b[N],A[N],Ans[N],head[N];
struct QAQ{int to,next;}a[N];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int pt[N];
struct Segment_Tree{
    #define pl (tr[p].lp)
    #define pr (tr[p].rp)
    #define mid ((L+R)>>1)
    int O;
    struct QAQ{int lp,rp,S;}tr[N*(logN+1)];//注意一次单点修改的使用空间是\ceil(log_2^N)+1
    inline void pushup(Re p){tr[p].S=tr[pl].S+tr[pr].S;}
    inline void change(Re &p,Re L,Re R,Re x){
        p=++O,++tr[p].S;
        if(L==R)return;
        if(x<=mid)change(pl,L,mid,x);
        else change(pr,mid+1,R,x);
    }
    inline int merge(Re p,Re q,Re L,Re R){
        if(!p||!q)return p+q;
        if(L==R){tr[p].S+=tr[q].S;return p;}
        pl=merge(pl,tr[q].lp,L,mid);
        pr=merge(pr,tr[q].rp,mid+1,R);
        pushup(p);return p;
    }
    inline int ask(Re &p,Re L,Re R,Re l,Re r){
        if(!p)return 0;
        if(l<=L&&R<=r)return tr[p].S;
        Re ans=0;
        if(l<=mid)ans+=ask(pl,L,mid,l,r);
        if(r>mid)ans+=ask(pr,mid+1,R,l,r);
        return ans;
    }
}TR;
inline void dfs(Re x,Re fa){
    TR.change(pt[x],1,m,A[x]);
    for(Re i=head[x],to;i;i=a[i].next)
        dfs(to=a[i].to,x),pt[x]=TR.merge(pt[x],pt[to],1,m);
    if(A[x]<m)Ans[x]=TR.ask(pt[x],1,m,A[x]+1,m);
}
int main(){
    in(n);
    for(Re i=1;i<=n;++i)in(A[i]),b[i]=A[i];
    sort(b+1,b+n+1),m=unique(b+1,b+n+1)-b-1;
    for(Re i=1;i<=n;++i)A[i]=lower_bound(b+1,b+m+1,A[i])-b;
    for(Re i=2;i<=n;++i)in(x),add(x,i);
    dfs(1,0);
    for(Re i=1;i<=n;++i)printf("%d\n",Ans[i]);
}
