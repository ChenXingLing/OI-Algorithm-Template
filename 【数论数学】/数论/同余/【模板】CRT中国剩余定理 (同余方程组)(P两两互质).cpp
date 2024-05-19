#include<cstdio>
#define LL long long
#define Re register LL
const int N=13;
LL n,ans,lcm=1,a[N],m[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void exgcd(Re a,Re b,Re &x,Re &y){
	if(!b){x=1,y=0;return;}
	exgcd(b,a%b,x,y);Re x0=x,y0=y;
	x=y0,y=x0-a/b*y0;return;
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
    for(Re i=1;i<=n;++i){
		Re x,y,M=lcm/m[i];exgcd(M,m[i],x,y);//M[i]*inv+m[i]*y=1
		x=(x%m[i]+m[i])%m[i],(ans+=cf(cf(a[i],M,lcm),x,lcm))%=lcm;
	}
	printf("%lld\n",ans);
}
