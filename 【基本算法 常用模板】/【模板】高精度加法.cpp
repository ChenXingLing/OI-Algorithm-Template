#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
template<typename T>inline void in(T &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
const int M=510;
char s[M];
struct Int{
	short a[M];int len;
	inline void In(){
		scanf("%s",s+1),len=strlen(s+1);
		for(Re i=1;i<=len;++i)a[i]=s[len-i+1]-'0';
	}
	inline void out(){for(Re i=len;i;--i)printf("%d",a[i]);}
	inline Int operator+=(const Int &O){
		len=max(len,O.len);
        for(Re i=1;i<=len;++i)a[i]+=O.a[i],a[i+1]+=a[i]/10,a[i]%=10;
		while(a[len+1])++len;
		return *this;
	}
}a,b;
int main(){a.In(),b.In(),(a+=b).out();}
