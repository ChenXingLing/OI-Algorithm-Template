#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define y1 ORZ_HYJ_AK_IOI
#define LL long long
#define Re register int
using namespace std;
const int N=1e4;
int a,b,c,d,n,m,pan1[N+5<<1],pan2[N+5<<1];LL ans;
struct Line{int x,y1,y2,k;inline bool operator<(Line O)const{return x==O.x?k>O.k:x<O.x;}}A[N+5<<1],B[N+5<<1];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int main(){
    // freopen("123.txt","r",stdin);
    in(n);
    for(Re i=1;i<=n;++i){
        in(a),in(b),in(c),in(d);
        A[++m]=(Line){a,b,d,1},B[m]=(Line){b,a,c,1};
        A[++m]=(Line){c,b,d,0},B[m]=(Line){d,a,c,0};
    }
    sort(A+1,A+m+1);
    sort(B+1,B+m+1);
    for(Re i=1;i<=m;++i){
        if(A[i].k)for(Re j=A[i].y1;j<A[i].y2;++j)ans+=(!pan1[j+N]),++pan1[j+N];
        else for(Re j=A[i].y1;j<A[i].y2;++j)--pan1[j+N],ans+=(!pan1[j+N]);
        if(B[i].k)for(Re j=B[i].y1;j<B[i].y2;++j)ans+=(!pan2[j+N]),++pan2[j+N];
        else for(Re j=B[i].y1;j<B[i].y2;++j)--pan2[j+N],ans+=(!pan2[j+N]);
    }
    printf("%lld\n",ans);
}
