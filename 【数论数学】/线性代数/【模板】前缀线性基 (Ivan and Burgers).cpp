#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=5e5+3,logN=20,inf=2e9;
int n,x,y,T;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct JI{
	int p[logN+1],ip[logN+1];JI(){memset(p,0,sizeof(p));}
	inline void insert(Re x,Re id){
		for(Re i=logN;i>=0;--i)
			if((x>>i)&1){
				if(!p[i]){p[i]=x,ip[i]=id;break;}
				if(ip[i]<id)swap(p[i],x),swap(ip[i],id);//注意这里要swap，不能直接赋值
				x^=p[i];
			}
	}
	inline int ask(Re L){
		Re ans=0;
		for(Re i=logN;i>=0;--i)if(ip[i]>=L)ans=max(ans,ans^p[i]);
		return ans;
	}
}A[N],S[N];
int main(){
//    freopen("456.txt","r",stdin);
    in(n);
    for(Re i=1;i<=n;++i)in(x),S[i]=S[i-1],S[i].insert(x,i);
    in(T);
    while(T--)in(x),in(y),printf("%d\n",S[y].ask(x));
}
