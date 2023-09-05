#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
using namespace std;
const int N=3e4+3,M=2e5+3;
int n,T,BL,ans,A[N],cnt[1000003],Ans[M];
struct Query{
    int l,r,id;
    inline bool operator<(const Query &O)const{
        Re B1=l/BL,B2=O.l/BL;
        return B1!=B2?B1<B2:((B1&1)?r<O.r:r>O.r);
    }
}Q[M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x){ans+=!cnt[x]++;}
inline void del(Re x){ans-=!--cnt[x];}
int main(){
    in(n),BL=sqrt(n)+1;
    for(Re i=1;i<=n;++i)in(A[i]);
    in(T);
    for(Re i=1;i<=T;++i)in(Q[i].l),in(Q[i].r),Q[i].id=i;
    sort(Q+1,Q+T+1);Re nowL=1,nowR=0;
    for(Re i=1;i<=T;++i){
        while(nowR<Q[i].r)add(A[++nowR]);
        while(nowR>Q[i].r)del(A[nowR--]);
        while(nowL>Q[i].l)add(A[--nowL]);
        while(nowL<Q[i].l)del(A[nowL++]);
        Ans[Q[i].id]=ans;
    }
    for(Re i=1;i<=T;++i)printf("%d\n",Ans[i]);
}
