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
const int M=4010;
char s[M];
struct Int{
	short a[M];int len;
	Int(){len=0;memset(a,0,sizeof(a));}
	inline void In(){
		scanf("%s",s+1),len=strlen(s+1);
		for(Re i=1;i<=len;++i)a[i]=s[len-i+1]-'0';
	}
	inline void out(){for(Re i=len;i;--i)printf("%d",a[i]);}
	inline Int operator*(const Int &O)const{
		Int ans;
        for(Re i=1;i<=len;++i){
			Re x=0;
			for(Re j=1;j<=O.len;++j)
				ans.a[i+j-1]+=a[i]*O.a[j]+x,x=ans.a[i+j-1]/10,ans.a[i+j-1]%=10;
			if(x)ans.a[i+O.len]=x;
		}
		ans.len=len+O.len;
		while(!ans.a[ans.len]&&ans.len>1)ans.len--;
		return ans;
	}
	inline Int operator*=(const Int &O){return *this=*this*O;}
}a,b;
int main(){a.In(),b.In(),(a*=b).out();}
