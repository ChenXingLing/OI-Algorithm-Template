#include<algorithm>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Re register int
#define Vector Point
using namespace std;
const LD eps=1e-13;
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}
LD a,b,c,d,L,R;
inline LD F(LD x){return (c*x+d)/(a*x+b);}
inline LD Simpson(LD L,LD R){return (R-L)*(F(L)+4.0*F((L+R)*0.5)+F(R))/6.0;}
inline LD sakura(LD L,LD R,LD now){
	LD mid=(L+R)*0.5,FL=Simpson(L,mid),FR=Simpson(mid,R);
	if(!dcmp(now-FL-FR))return now;
	return sakura(L,mid,FL)+sakura(mid,R,FR);
}
int main(){
//	freopen("123.txt","r",stdin);
	scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&L,&R);
	printf("%lf\n",sakura(L,R,Simpson(L,R)));
}
