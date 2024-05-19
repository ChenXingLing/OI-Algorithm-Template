#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=2e5+3,logN=18;
int n,m,x,y,z,T,b[N],A[N],pt[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct President_Tree{
    #define pl tr[p].lp
    #define pr tr[p].rp
    #define mid (L+R>>1)
    int O;
    struct QAQ{int S,lp,rp;}tr[N*(logN+1)];
    inline void creat(Re &p,Re q,Re L,Re R,Re w){
        p=++O,tr[p]=tr[q],++tr[p].S;
        if(L==R)return;
        if(w<=mid)creat(pl,tr[q].lp,L,mid,w);
        else creat(pr,tr[q].rp,mid+1,R,w);
    }
    inline int ask(Re p,Re q,Re L,Re R,Re k){
        if(L==R)return L;
        Re tmp=tr[pl].S-tr[tr[q].lp].S;
        if(tmp>=k)return ask(pl,tr[q].lp,L,mid,k);
        else return ask(pr,tr[q].rp,mid+1,R,k-tmp);
    }
}T1;
int main(){
//    freopen("123.txt","r",stdin);
    in(n),in(T);
    for(Re i=1;i<=n;++i)in(A[i]),b[i]=A[i];
    sort(b+1,b+n+1),m=unique(b+1,b+n+1)-b-1;
    for(Re i=1;i<=n;++i)T1.creat(pt[i],pt[i-1],1,m,lower_bound(b+1,b+m+1,A[i])-b);
    while(T--)in(x),in(y),in(z),printf("%d\n",b[T1.ask(pt[y],pt[x-1],1,m,z)]);
}
