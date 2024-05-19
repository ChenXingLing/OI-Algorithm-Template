#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Re register int
using namespace std;
const int N=1e6+3;
int n,HYJ,X[N],Y[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline LD calc(LD x,LD y){
	LD tmp=0;
	for(Re i=1;i<=n;++i)tmp+=sqrt((x-X[i])*(x-X[i])+(y-Y[i])*(y-Y[i]));
	return tmp;
}
inline void Srand(Re seed){
	srand(seed);Re a=rand()%10+1;
	while(a--)srand(rand());
}
LD ans,ansx,ansy;
const LD deltaT=0.99,maxT=4995,minT=1e-12;
inline void fire(){
	LD x=ansx,y=ansy,nowT=maxT;
	while(nowT>minT){
		LD nx=x+((rand()<<1)-RAND_MAX)*nowT;
		LD ny=y+((rand()<<1)-RAND_MAX)*nowT;
		LD nans=calc(nx,ny),deltaE=nans-ans;
		if(deltaE<0)ans=nans,ansx=x=nx,ansy=y=ny;
		else if(exp(-deltaE/nowT)>(LD)rand()/RAND_MAX)x=nx,y=ny;
		nowT*=deltaT;
	}
}
int main(){
//	freopen("123.txt","r",stdin);
	in(HYJ),Srand(20030825);
	while(HYJ--){
		in(n);
		for(Re i=1;i<=n;++i)in(X[i]),in(Y[i]);
		ans=calc(X[1],Y[1]),ansx=X[1],ansy=Y[1];
		fire(),fire(),fire(),fire(),fire();
		printf("%.lf\n",ans);
		if(HYJ)puts("");
	}
}
