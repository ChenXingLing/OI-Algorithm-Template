#include<cstdio>
#define LL long long
#define Re register LL
using namespace std;
const LL N=1e4+3,P=19260817;
LL a,b;
inline void in(Re &x){
    Re f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),x%=P,c=getchar();
}
inline LL mi(Re x,Re k){
    Re s=1;
    while(k){
        if(k&1)(s*=x)%=P;
        (x*=x)%=P,k>>=1;
    }
    return s;
}
int main(){
    // freopen("123.txt","r",stdin);
    in(a),in(b);
    if(b)printf("%lld\n",a%P*mi(b,P-2)%P);
    else puts("Angry!");
}