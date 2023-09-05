#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int n,m,T,b[N<<1],A[N];char op[N];
struct QWQ{int x,y,k;}Q[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int t1,t2,pt[N],ptl[20],ptr[20];
struct President_Tree{
    #define pl (tr[p].lp)
    #define pr (tr[p].rp)
    #define mid ((L+R)>>1)
    int O;
    struct QAQ{int S,lp,rp;}tr[(N<<1)*200];
    inline void change(Re &p,Re L,Re R,Re x,Re v){
        if(!p)p=++O;tr[p].S+=v;
        if(L==R)return;
        if(x<=mid)change(pl,L,mid,x,v);
        else change(pr,mid+1,R,x,v);
    }
    inline int ask(Re p,Re L,Re R,Re K){
        if(L==R)return L;
        Re tmp=0;
        for(Re i=1;i<=t1;++i)tmp-=tr[tr[ptl[i]].lp].S;
        for(Re i=1;i<=t2;++i)tmp+=tr[tr[ptr[i]].lp].S;
        if(K<=tmp){
            for(Re i=1;i<=t1;++i)ptl[i]=tr[ptl[i]].lp;
            for(Re i=1;i<=t2;++i)ptr[i]=tr[ptr[i]].lp;
            return ask(pl,L,mid,K);
        }
        else{
            for(Re i=1;i<=t1;++i)ptl[i]=tr[ptl[i]].rp;
            for(Re i=1;i<=t2;++i)ptr[i]=tr[ptr[i]].rp;
            return ask(pr,mid+1,R,K-tmp);
        }
    }
}SG;
struct BIT{
    inline void add(Re x,Re v){
        for(Re i=x;i<=n;i+=i&-i)SG.change(pt[i],1,m,A[x],v);
    }
    inline int ask(Re L,Re R,Re k){
        t1=t2=0;
        for(Re i=L-1;i;i-=i&-i)ptl[++t1]=pt[i];
        for(Re i=R;i;i-=i&-i)ptr[++t2]=pt[i];
        return SG.ask(1,1,m,k);
    }
}TR;
int main(){
    in(n),in(T),m=n;
    for(Re i=1;i<=n;++i)in(A[i]),b[i]=A[i];
    for(Re i=1;i<=T;++i){
        scanf(" %c",&op[i]),in(Q[i].x),in(Q[i].y);
        if(op[i]=='Q')in(Q[i].k);
        else b[++m]=Q[i].y;
    }
    sort(b+1,b+m+1),m=unique(b+1,b+m+1)-b-1;
    for(Re i=1;i<=n;++i)A[i]=lower_bound(b+1,b+m+1,A[i])-b;
    for(Re i=1;i<=T;++i)if(op[i]=='C')Q[i].y=lower_bound(b+1,b+m+1,Q[i].y)-b;
    for(Re i=1;i<=n;++i)TR.add(i,1);
    for(Re i=1;i<=T;++i){
        if(op[i]=='Q')printf("%d\n",b[TR.ask(Q[i].x,Q[i].y,Q[i].k)]);
        else TR.add(Q[i].x,-1),A[Q[i].x]=Q[i].y,TR.add(Q[i].x,1);
    }
}
