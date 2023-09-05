#include<cstdio>
#define LL long long
#define Re register LL
const int N=1e5+3;
LL n,ans,lcm=1,a[N],m[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline LL exgcd(Re a,Re b,Re &x,Re &y){
	if(!b){x=1,y=0;return a;}
	Re gcd=exgcd(b,a%b,x,y);Re x0=x,y0=y;
	x=y0,y=x0-a/b*y0;return gcd;
}
inline LL cf(Re x,Re k,Re P){
	Re s=0;
	while(k){
		if(k&1)(s+=x)%=P;
		(x+=x)%=P,k>>=1;
	}
	return s;
}
int main(){
//    freopen("123.txt","r",stdin);
    in(n);
    for(Re i=1;i<=n;++i)in(m[i]),in(a[i]),lcm*=m[i];
    ans=a[1]%m[1],lcm=m[1];
    for(Re i=2;i<=n;++i){//ans+lcm*k=a[i](mod m[i]) -> lcm*k=a[i]-ans(mod m[i]) -> lcm*k+m[i]*y=a[i]-ans
		Re c=((a[i]-ans)%m[i]+m[i])%m[i],x,y;
		Re gcd=exgcd(lcm,m[i],x,y);
		Re k=cf(x,c/gcd,m[i]/gcd);
		ans+=lcm*k,lcm*=m[i]/gcd,ans=(ans%lcm+lcm)%lcm;
	}
	printf("%lld\n",ans);
}
