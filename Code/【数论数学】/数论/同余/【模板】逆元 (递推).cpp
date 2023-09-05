#include<cstdio>
#define LL long long
#define Re register int
const int N=3e6+3;
int n,P,inv[N];
int main(){
    scanf("%d%d",&n,&P);
    inv[1]=1;
    for(Re i=2;i<=n;++i)inv[i]=(LL)(P-P/i)*inv[P%i]%P;
    for(Re i=1;i<=n;++i)printf("%d\n",inv[i]);
}
