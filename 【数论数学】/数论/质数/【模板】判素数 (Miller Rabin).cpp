#include<cstdio>
#define LL long long
#define Re register LL
LL n,prime[10]={2,3,5,7,11,13,17,19,23,29};
inline LL cf(Re x,Re k,Re P){
	Re s=0;
	while(k){
		if(k&1)(s+=x)%=P;
		(x<<=1)%=P,k>>=1;
	}
	return s%P;
}
inline LL mi(Re x,Re k,Re P){
	Re s=1;
    while(k){
    	if(k&1)s=cf(s,x,P)%P;
    	x=cf(x,x,P)%P,k>>=1;
    }
    return s%P;
}
inline bool Miller_Rabin(Re x){
    Re s=0,t=x-1;
    if(x==2)return 1;
    if(x<2||!(x&1))return 0;
    while(!(t&1))s++,t>>=1;
    for(Re i=0;i<10&&prime[i]<x;++i){
        Re a=prime[i],b=mi(a,t,x);
        for(Re j=1,k;j<=s;++j){
            k=cf(b,b,x);
            if(k==1&&b!=1&&b!=x-1)return 0;
            b=k;
        }
        if(b!=1)return 0;
    }
    return 1;
}
int main(){
	while(scanf("%lld",&n)!=EOF)puts(Miller_Rabin(n)?"Y":"N");
}
