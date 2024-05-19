/*
                    n   m                 n   m                   n   m             n   m
s[x][y]=(x+1)*(y+1)*¡Æ  ¡Æa[i][j] - (y+1)*¡Æ  ¡Æa[i][j]*i - (x+1)*¡Æ  ¡Æa[i][j]*j + ¡Æ  ¡Æa[i][j]*i*j
                   i=1 j=1               i=1 j=1                 i=1 j=1           i=1 j=1
*/
#include<cstdio>
#define y1 yyyy
#define LL long long
#define Re register int
const int N=2048+3;
int n,m,x,x1,y1,x2,y2,op;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct BIT{
    LL C1[N][N],C2[N][N],C3[N][N],C4[N][N];
    inline void add(Re x,Re y,Re v){
        Re i=x;
        while(i<=n){
            Re j=y;
            while(j<=m)C1[i][j]+=v,C2[i][j]+=(LL)x*v,C3[i][j]+=(LL)y*v,C4[i][j]+=(LL)x*y*v,j+=j&-j;
            i+=i&-i;
        }
    }
    inline void add(Re x1,Re y1,Re x2,Re y2,Re z){
        add(x1,y1,z),add(x1,y2+1,-z),add(x2+1,y1,-z),add(x2+1,y2+1,z);
    }
    inline LL ask(Re x,Re y){
        Re i=x;LL ans=0;
        while(i){
            Re j=y;
            while(j)ans+=(LL)(x+1)*(y+1)*C1[i][j]-(LL)(y+1)*C2[i][j]-(LL)(x+1)*C3[i][j]+C4[i][j],j-=j&-j;
            i-=i&-i;
        }
        return ans;
    }
    inline LL ask(Re x1,Re y1,Re x2,Re y2){
        return ask(x2,y2)-ask(x2,y1-1)-ask(x1-1,y2)+ask(x1-1,y1-1);
    }
}TR;
int main(){
    in(n),in(m);
    while(~scanf("%d",&op)){
        in(x1),in(y1),in(x2),in(y2);
        if(op<2)in(x),TR.add(x1,y1,x2,y2,x);
        else printf("%lld\n",TR.ask(x1,y1,x2,y2));
    }
}
