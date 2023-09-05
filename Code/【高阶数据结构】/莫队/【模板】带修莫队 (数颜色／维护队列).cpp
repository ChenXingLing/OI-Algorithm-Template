#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define Re register int
using namespace std;
const int N=2e5+3,M=2e5+3,INF=1e6+3;
int n,x,y,T,TQ,TC,BL,ans,a[N],Ans[M],cnt[INF];char op;
struct Query{
    int l,r,id,time;
    inline bool operator<(const Query &O)const{
        Re B1=l/BL,B2=O.l/BL,B3=r/BL,B4=O.r/BL;
        return B1!=B2?B1<B2:(B3!=B4?B3<B4:time<O.time);
    }
}Q[N];
struct Change{int w,co;}C[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x){ans+=!cnt[x]++;}
inline void del(Re x){ans-=!--cnt[x];}
int main(){
//    freopen("123.txt","r",stdin);
    in(n),in(T),BL=pow(n,2.0/3.0);
    for(Re i=1;i<=n;++i)in(a[i]);
    for(Re i=1;i<=T;++i){
    	scanf(" %c",&op);
    	in(x),in(y);
    	if(op=='Q')++TQ,Q[TQ]=(Query){x,y,TQ,TC};
    	else C[++TC]=(Change){x,y};
	}
    sort(Q+1,Q+TQ+1);
    Re nowL=1,nowR=0,nowT=0;
    for(Re i=1;i<=TQ;++i){
        while(nowL<Q[i].l)del(a[nowL++]);
        while(nowL>Q[i].l)add(a[--nowL]);
        while(nowR>Q[i].r)del(a[nowR--]);
        while(nowR<Q[i].r)add(a[++nowR]);
        while(nowT<Q[i].time){
        	Re w=C[++nowT].w;
        	if(nowL<=w&&w<=nowR)del(a[w]),add(C[nowT].co);
        	swap(a[w],C[nowT].co);
		}
		while(nowT>Q[i].time){
			Re w=C[nowT].w;
        	if(nowL<=w&&w<=nowR)del(a[w]),add(C[nowT].co);
        	swap(a[w],C[nowT--].co);
		}
        Ans[Q[i].id]=ans;
    }
    for(Re i=1;i<=TQ;++i)printf("%d\n",Ans[i]);
}
