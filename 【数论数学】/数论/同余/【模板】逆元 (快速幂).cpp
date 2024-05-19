#include<cstdio>
#define LL long long
#define Re register int
int n,P;
inline int inv(Re x,Re P){
    Re s=1,k=P-2;
    while(k){
    	if(k&1)s=(LL)s*x%P;
    	x=(LL)x*x%P,k>>=1;
    }
    return s%P;
}
int main(){
    scanf("%d%d",&n,&P);
    for(Re i=1;i<=n;++i)printf("%d\n",inv(i,P));
}
