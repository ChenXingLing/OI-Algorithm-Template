#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#include<algorithm>
#include<cstdio>
#define Re register int
#define F(i,a,b) for(Re i=a;i<=b;++i)
#define lo(o) lower_bound(b+1,b+m+1,o)-b
#define P(x) if(op[i]==x)
using namespace std;
const int N=1e5+3,inf=2147483647;
int m,T,fu,C[N],a[N],b[N],Q[N],op[N]; 
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void add(Re x,Re v){while(x<=m)C[x]+=v,x+=x&-x;}
inline int ask(Re x){
	Re ans=0;
	while(x>0)ans+=C[x],x-=x&-x;
	return ans;
}
inline int ask_kth(Re k){
	Re l=0,r=m;
	while(l<r){
		Re mid=l+r>>1;
		if(ask(mid)>=k)r=mid;
		else l=mid+1;
	}
	return b[l];
}
int main(){
	in(T); 
    F(i,1,T){
    	in(op[i]),in(Q[i]);
    	if(op[i]!=4)b[++m]=Q[i];
    }
    sort(b+1,b+m+1),m=unique(b+1,b+m+1)-b-1;
    F(i,1,T){
    	P(1)add(lo(Q[i]),1);
    	P(2)add(lo(Q[i]),-1);
		P(3)printf("%d\n",ask(lo(Q[i])-1)+1);
		P(4)printf("%d\n",ask_kth(Q[i]));
		P(5)printf("%d\n",ask_kth(ask(lo(Q[i])-1)));
		P(6)printf("%d\n",ask_kth(ask(lo(Q[i]))+1));
    }
}
