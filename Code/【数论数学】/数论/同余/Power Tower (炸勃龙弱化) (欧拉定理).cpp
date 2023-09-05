#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
#include<cmath>
#include<map>
#define LL long long
#define Re register LL
using namespace std;
const int N=1e5+3;
LL n,l,r,T,P,fu,a[N];char ch;map<LL,LL>phi;
inline void in(Re &x){
    x=fu=0;ch=getchar();
    while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();x=fu?-x:x;
}
inline LL Phi(Re x){
    Re ans=x,pos=x;
    if(phi.count(x))return phi[x];
    for(Re i=2;i<=sqrt(x);i++)
        if(!(x%i)){
            ans=ans/i*(i-1);
            while(!(x%i)) x/=i;
        }
    if(x>1)ans=ans/x*(x-1);
    return phi[pos]=ans;
}
inline LL mi(Re x,Re k,Re P){
    Re s=1,ok=0,flag=0;ok|=(x>=P);x%=P;
    while(k){
        if(k&1){s*=x;flag|=(ok||s>=P);s%=P;}
        x*=x;ok|=(x>=P);x%=P;k>>=1;
    }
    return s+(flag?P:0);
}
inline LL sakura(Re l,Re r,Re P){
    if(P==1|l>r)return 1;
    return mi(a[l],sakura(l+1,r,Phi(P)),P);
}
int main(){
    in(n),in(P);
    for(Re i=1;i<=n;++i)in(a[i]);
    in(T);
    while(T--){
        in(l),in(r);
    	printf("%lld\n",sakura(l,r,P)%P);
    }
}
