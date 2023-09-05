#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#include<algorithm>
#include<cstdio>
#define LL long long
#define Re register LL
using namespace std;
LL ans,fu,S,d,k,n,t,i,x;
struct QAQ{LL x,d;inline bool operator<(QAQ b)const{return x==b.x?d<b.d:x<b.x;}}Q[100011];
inline void up(Re p){
	while(p>1)
		if(Q[p]<Q[p>>1])swap(Q[p],Q[p>>1]),p>>=1;
		else break;
}
inline void down(Re p){
	int s=p<<1;
	while(s<=t){
		if(s<t&&Q[s|1]<Q[s])s++;
		if(Q[s]<Q[p])swap(Q[s],Q[p]),p=s,s<<=1;
		else break;
	}
}
inline void push(Re x,Re d){Q[++t].x=x,Q[t].d=d;up(t);}
inline void delet(Re p){swap(Q[p],Q[t--]);down(p);}
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(fu)x=-x;
}
int main(){
	in(n),in(k);
	while(n--)in(x),push(x,0);
	while((t-1)%(k-1))push(0,0);
	while(t>1){
		x=k,S=0,d=0;
		while(x--)d=max(d,Q[1].d),S+=Q[1].x,delet(1);
		ans+=S,push(S,d+1);
	}
	printf("%lld\n%lld",ans,Q[1].d);
}
