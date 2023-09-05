#pragma GCC diagnostic error "-std=c++11"
#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<cstdio>
#include<cmath>
#define Re register int
#define F(x,a,b) for(Re x=a;x<=b;++x)
const int N=1e5+3,T=330;
int n,t,x,l,r,Q,fu,pt[N],L[T],R[T],a[N],tag[T];
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline int sak(Re l,Re r,Re p,Re x){
    Re tmp=0;
    if(tag[p]!=-1){F(i,L[p],R[p])a[i]=tag[p];tmp+=(r-l+1)*(tag[p]==x);}
    else F(i,l,r)tmp+=a[i]==x;
    tag[p]=-1;F(i,l,r)a[i]=x;
    return tmp;
}
inline int fuck(Re p,Re x){
    Re tmp=0;
    if(tag[p]!=-1){F(j,L[p],R[p])a[j]=tag[p];tmp+=(R[p]-L[p]+1)*(tag[p]==x);}
    else F(j,L[p],R[p])tmp+=a[j]==x;
    tag[p]=x;
    return tmp;
}
inline int sovle(Re l,Re r,Re x){
    Re p=pt[l],q=pt[r],ans=0;
    if(p==q)return l==r?fuck(p,x):sak(l,r,p,x);
    else{
        F(i,p+1,q-1)ans+=fuck(i,x);
        ans+=sak(l,R[p],p,x)+sak(L[q],r,q,x);
    }
    return ans;
}
int main(){
    in(n),t=sqrt(Q=n);
    F(i,1,t)L[i]=(i-1)*t+1,R[i]=i*t;
    if(R[t]<n)R[++t]=n,L[t]=R[t-1]+1;
    F(i,1,n)in(x),a[i]=x;
    F(i,1,t){tag[i]=-1;F(j,L[i],R[i])pt[j]=i;}
    while(Q--){
        in(l),in(r),in(x);
        printf("%d\n",sovle(l,r,x));
    }
}
