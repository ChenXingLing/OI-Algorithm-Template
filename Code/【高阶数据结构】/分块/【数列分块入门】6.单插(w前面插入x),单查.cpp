#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<vector>
#include<cstdio>
#include<cmath>
#define Re register int
#define F(x,a,b) for(Re x=a;x<=b;++x)
using namespace std;
const int N=1e5+3,T=330;
int n,o,t,x,l,r,Q,fu,pt[N],pw[N],L[T],R[T];
vector<int>a[T];
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void change(Re w,Re x){
    F(i,1,t)
        if(w>a[i].size())w-=a[i].size();
        else{a[i].insert(a[i].begin()+w-1,x);return;}
}
inline int ask(Re w){
    F(i,1,t)
        if(w>a[i].size())w-=a[i].size();
        else return a[i][w-1];
}
int main(){
    in(n),t=sqrt(Q=n);
    F(i,1,t)L[i]=(i-1)*t+1,R[i]=i*t;
    if(R[t]<n)R[++t]=n,L[t]=R[t-1]+1;
    F(i,1,t){F(j,L[i],R[i])in(x),a[i].push_back(x),pt[j]=i;}
    while(Q--){
        in(o),in(l),in(r),in(x);
        if(o)printf("%d\n",ask(r));
        else change(l,r);
    }
}
