#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Re register int
using namespace std;
const int N=103;
int n;LD eps=1e-8,a[N][N];
inline int dcmp(Re a){return a<-eps?-1:(a>eps?1:0);}
inline LD Abs(LD a){return dcmp(a)*a;}
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n);
	for(Re i=1;i<=n;++i)	
		for(Re j=1;j<=n+1;++j)
			scanf("%lf",&a[i][j]);
	for(Re j=1;j<=n;++j){
		Re w=j;
		for(Re i=j+1;i<=n;++i)
			if(dcmp(Abs(a[i][j])-Abs(a[w][j]))>0)w=i;
		for(Re k=1;k<=n+1;++k)swap(a[j][k],a[w][k]);
		if(!dcmp(a[j][j]))return !puts("No Solution");
		for(Re i=1;i<=n;++i)
			if(i!=j){
				LD tmp=a[i][j]/a[j][j];
				for(Re k=j;k<=n+1;++k)a[i][k]-=a[j][k]*tmp;
			}
	}
	for(Re i=1;i<=n;++i)printf("%.2lf\n",a[i][n+1]/a[i][i]);
}
