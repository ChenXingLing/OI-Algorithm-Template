#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm>
#include<cstdio>
#include<cmath>
#define inf -2147483647
#define Re register int
#define F(x,a,b) for(Re x=a;x<=b;++x)
using namespace std;
const int N=1e5+3,T=330;
int n,t,x,l,r,o,Q,fu,pt[N],L[T],R[T],a[N],b[N],add[T];
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void sak(Re l,Re r,Re p,Re x){F(i,l,r)a[i]+=x;F(i,L[p],R[p])b[i]=a[i];sort(b+L[p],b+R[p]+1);}
inline void change(Re l,Re r,Re x){
    Re p=pt[l],q=pt[r];
    if(p==q)sak(l,r,p,x);
    else{
        F(i,p+1,q-1)add[i]+=x;
        sak(l,R[p],p,x),sak(L[q],r,q,x);
    }
}
inline int ask(Re l,Re r,Re x){
    Re p=pt[l],q=pt[r],ans=inf,w;
    if(p==q){F(i,l,r)if(a[i]+add[p]<x)ans=max(ans,a[i]+add[p]);}
    else{
        F(i,p+1,q-1)w=lower_bound(b+L[i],b+R[i]+1,x-add[i])-(b+1),ans=w>=L[i]?max(ans,b[w]+add[i]):ans;
        F(i,l,R[p])if(a[i]+add[p]<x)ans=max(ans,a[i]+add[p]);
        F(i,L[q],r)if(a[i]+add[q]<x)ans=max(ans,a[i]+add[q]);
    }
    return ans==inf?-1:ans;
}
int main(){
    in(n),t=sqrt(Q=n);
    F(i,1,t)L[i]=(i-1)*t+1,R[i]=i*t;
    if(R[t]<n)R[++t]=n,L[t]=R[t-1]+1;
    F(i,1,n)in(x),a[i]=b[i]=x;
    F(i,1,t)F(j,L[i],R[i])pt[j]=i;
    F(i,1,t)sort(b+L[i],b+R[i]+1);
    while(Q--){
        in(o),in(l),in(r),in(x);
        if(o)printf("%d\n",ask(l,r,x));
        else change(l,r,x);
    }
}
