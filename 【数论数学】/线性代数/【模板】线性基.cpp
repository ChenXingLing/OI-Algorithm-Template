#include<algorithm>
#include<cstdio>
#define LL long long
#define Re register LL
using namespace std;
const int N=55;
LL n,x,ans,p[N];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline void insert(Re x){
	for(Re i=50;i>=0;--i)
		if((x>>i)&1){
			if(!p[i]){p[i]=x;break;}
			x^=p[i];
		}
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n);
	for(Re i=1;i<=n;++i)in(x),insert(x);
	for(Re i=50;i>=0;--i)ans=max(ans,ans^p[i]);
	printf("%lld\n",ans);
}
