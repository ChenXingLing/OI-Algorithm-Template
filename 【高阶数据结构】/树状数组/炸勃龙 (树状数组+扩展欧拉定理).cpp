#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
#define LL long long
#define Re register LL
#define F(a,b) for(i=a;i<=b;++i)
const int N=5e5+3,Np=2e7;
LL i,j,n,x,l,r,K,T,fu,cnt,c[N],C[N],pan[Np+1],pri[Np+1],phi[Np+1];char ch;
inline void in(Re &x){
    x=fu=0;ch=getchar();
    while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();x=fu?-x:x;
}
inline void add(Re x,Re k){while(x<=n)C[x]+=k,x+=x&-x;}
inline LL ask(Re x){Re tmp=0;while(x)tmp+=C[x],x-=x&-x;return tmp;}
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
    return mi(ask(l),sakura(l+1,r,phi[P]),P);
}
int main(){
    for(i=2;i<=Np;++i){
        if(!pan[i])pri[++cnt]=i,phi[i]=i-1;
        for(j=1;j<=cnt;++j){
      		if(i*pri[j]>Np)break;
      		pan[i*pri[j]]=1;
      		if(i%pri[j])phi[i*pri[j]]=phi[i]*(pri[j]-1);
      		else{phi[i*pri[j]]=phi[i]*pri[j];break;}
   		}
    }
    in(n),in(T);
    F(1,n)in(x),add(i,x-l),l=x;
    while(T--){
        in(K),in(l),in(r),in(x);
        if(K<2)add(l,x),add(r+1,-x);
        else printf("%lld\n",sakura(l,r,x)%x);
    }
}
