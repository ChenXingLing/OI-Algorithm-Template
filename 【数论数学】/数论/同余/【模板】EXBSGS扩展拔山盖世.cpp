#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#define LL long long
#define Re register int
using namespace std;
int x,y,z;map<int,int>B;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int mi(Re x,Re k,Re P){
	Re s=1;
	while(k){
		if(k&1)s=(LL)s*x%P;
		x=(LL)x*x%P,k>>=1;
	}
	return s;
}
inline int gcd(Re a,Re b){return !b?a:gcd(b,a%b);}
inline void exBSGS(Re x,Re y,Re P){
	if(y==1){puts("0");return;}
	Re d=gcd(x,P),tmp=1,t=0;
	while(d!=1){
		if(y%d){puts("No Solution");return;}
		++t,y/=d,P/=d,tmp=(LL)tmp*(x/d)%P;
		if(y==tmp){printf("%d\n",t);return;}
		d=gcd(x,P);
	}
	Re m=sqrt(P)+1;B.clear();
	for(Re b=0,s=y;b<m;++b)B[s]=b,s=(LL)s*x%P;
	Re s=tmp;tmp=mi(x,m,P);
	for(Re a=1;a<=m;++a){
		s=(LL)s*tmp%P;
		if(B.find(s)!=B.end()){printf("%d\n",a*m-B[s]+t);return;}
	}
	puts("No Solution");
}
int main(){
//	freopen("123.txt","r",stdin);
	while(1){
		in(x),in(y),in(z);
		if(!x&&!y&&!z)break;
		exBSGS(x,z,y);
	}
}
