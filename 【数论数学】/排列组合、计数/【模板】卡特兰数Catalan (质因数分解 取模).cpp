#include<cstdio>
#define LL long long
#define Re register LL
const int N=1e6+3;
LL n,P,cnt,pri[N],pan[N<<1];
inline void get_pri(Re N){
    for(Re i=2;i<=N;++i){
        if(!pan[i])pri[++cnt]=i;
        for(Re j=1;j<=cnt&&i*pri[j]<=N;++j)pan[i*pri[j]]=1;
    }
}
inline LL Catalan(Re n){
    Re ans=1;cnt=0;get_pri(n<<1);
    for(Re i=1;i<=cnt;i++){
        Re x=pri[i],t=0;
        while(x<=2*n){t+=2*n/x-n/x-(n+1)/x;x*=pri[i];}
        while(t--)(ans*=pri[i])%=P;
    }
    return ans%P;
}
int main(){
    scanf("%lld%lld",&n,&P);
	printf("%lld",Catalan(n));
}
