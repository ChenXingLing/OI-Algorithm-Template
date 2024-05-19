#include<algorithm>
#include<cstring>
#include<cstdio>
#define y1 yyyy
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int n,m,T,x1,y1,x2,y2,b[N<<1];LL ans;
struct Line{int x,y1,y2,k;inline bool operator<(const Line &O)const{return x<O.x;}}A[N<<1];
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
    struct QAQ{int cnt,len;}tr[N<<3];//因为离散化,这里要开8倍
    inline void pushup(Re p,Re L,Re R){
        if(tr[p].cnt)tr[p].len=b[R+1]-b[L];//注意这里是b[R+1]-b[L]
        else tr[p].len=(L==R)?0:tr[pl].len+tr[pr].len;
    }
    inline void change(Re p,Re L,Re R,Re l,Re r,Re v){
        if(l<=L&&R<=r){tr[p].cnt+=v,pushup(p,L,R);return;}
        if(l<=mid)change(pl,L,mid,l,r,v);
        if(r>mid)change(pr,mid+1,R,l,r,v);
        pushup(p,L,R);
    }
}TR;
int main(){
    in(T);
    while(T--){
        in(x1),in(y1),in(x2),in(y2);
        A[++n]=(Line){x1,y1,y2,1},A[++n]=(Line){x2,y1,y2,-1};
        b[++m]=y1,b[++m]=y2;
    }
    sort(A+1,A+n+1),sort(b+1,b+m+1),m=unique(b+1,b+m+1)-b-1;
    for(Re i=1;i<n;++i){
        Re y1=lower_bound(b+1,b+m+1,A[i].y1)-b,y2=lower_bound(b+1,b+m+1,A[i].y2)-b;
        TR.change(1,1,m-1,y1,y2-1,A[i].k);
        ans+=(LL)TR.tr[1].len*(A[i+1].x-A[i].x);
    }
    printf("%lld\n",ans);
}
