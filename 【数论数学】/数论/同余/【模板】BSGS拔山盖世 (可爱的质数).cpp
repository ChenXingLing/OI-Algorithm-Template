#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int x,y,m,P;map<int,int>B;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
//x^k = y (mod P)
//k = am-b (m=sqrt(P)+1, a\in[1,m], b\in[0,m-1])
//(x^m)^a = y x^b (mod P)
inline int mi(Re x,Re k){
	Re s=1;
	while(k){
		if(k&1)s=(LL)s*x%P;
		x=(LL)x*x%P,k>>=1;
	}
	return s;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(P),in(x),in(y),m=sqrt(P)+1;
	if(y==1)return !puts("0");
	for(Re b=0,s=y;b<m;++b)B[s]=b,s=(LL)s*x%P;
	Re tmp=mi(x,m);
	for(Re a=1,s=1;a<=m;++a){
		s=(LL)s*tmp%P;
		if(B.find(s)!=B.end()){printf("%d\n",a*m-B[s]);return 0;}
	}
	puts("no solution");
}
