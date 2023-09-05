#include<cstdio>
#define LD double
#define Re register int
const int N=15;
const LD eps=1e-6;
int n;LD l,r,a[N];
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}
inline LD F(LD x){
	LD s=0;
	for(Re i=0;i<=n;++i)s=s*x+a[i];
	return s;
}
int main(){
	scanf("%d%lf%lf",&n,&l,&r);
	for(Re i=0;i<=n;++i)scanf("%lf",&a[i]);
	while(dcmp(l-r)<0){
		LD mid=(l+r)/2.0;
		if(F(mid+eps)>F(mid-eps))l=mid;
		else r=mid;
	}
	printf("%.5lf",l);
}
