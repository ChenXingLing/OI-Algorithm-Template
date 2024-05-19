#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=3e5+5;
int n,s[N<<1];
inline void in(Re &x){
    Re f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int main(){
	in(n);
	for(Re i=1;i<=n;++i)in(s[i]),s[i+n]=s[i];
	Re i=1,j=2;
	while(i<=n&&j<=n){
		Re k=1;
		while(k<=n&&s[i+k-1]==s[j+k-1])++k;
		if(k>n)break;
		if(s[i+k-1]>s[j+k-1])i+=k;
		else j+=k;
		if(i==j)++i;
	}
	Re st=min(i,j);
	for(Re i=0;i<n;++i)printf("%d ",s[st+i]);
}
