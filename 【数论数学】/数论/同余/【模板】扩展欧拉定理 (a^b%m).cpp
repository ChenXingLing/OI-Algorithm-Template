#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
#include<cctype>
#define LL long long
#define Re register LL
LL i,a,b,m,x,s,phi,flag;char c;
inline LL cf(Re x,Re k){
	Re s=0;
	while(k){
		if(k&1)(s+=x)%=m;
		(x<<=1)%=m,k>>=1;
	}
	return s;
}
int main(){
    scanf("%lld%lld",&a,&m);phi=x=m;
    for(i=2;i*i<=m;++i)if(!(x%i)){phi-=phi/i;while(!(x%i))x/=i;}
    if(x>1)phi-=phi/x;
    while(!isdigit(c=getchar()));
    while(isdigit(c))flag|=((b=(b<<1)+(b<<3)+(c^48))>=phi),b%=phi,c=getchar();
    b+=flag?phi:0;x=1;
    while(b){if(b&1)x=cf(x,a)%m;a=cf(a,a)%m,b>>=1;}
    printf("%lld",x);
}
