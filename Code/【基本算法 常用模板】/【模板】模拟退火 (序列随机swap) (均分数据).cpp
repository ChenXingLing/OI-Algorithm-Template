#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Re register int
using namespace std;
const int N=23;
int n,m,S,A[N];LD x0;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void Srand(Re seed){
	srand(seed);Re a=rand()%10+1;
	while(a--)srand(rand());
}
inline void Random(Re *A,Re n){
	for(Re i=1;i<=n;++i)swap(A[i],A[rand()%n+1]);
}
int x[N];
inline LD calc(Re *A){
	for(Re i=1;i<=m;++i)x[i]=0;
	for(Re i=1;i<=n;++i){
		Re w=1;
		for(Re j=2;j<=m;++j)if(x[j]<x[w])w=j;
		x[w]+=A[i];
	}
	LD tmp=0;
	for(Re i=1;i<=m;++i)tmp+=(x[i]-x0)*(x[i]-x0);
	return tmp/m;
}
int nowA[N],ansA[N];LD ans;
const LD deltaT=0.995,maxT=4995,minT=1e-15;
inline void fire(){
	for(Re i=1;i<=n;++i)nowA[i]=ansA[i];LD nowT=maxT;
	while(nowT>minT){
		Re x=rand()%n+1,y=rand()%n+1;
		swap(nowA[x],nowA[y]);
		LD nans=calc(nowA),deltaE=nans-ans;
		if(deltaE<0){for(Re i=1;i<=n;++i)ansA[i]=nowA[i];ans=nans;}
		else if(exp(-deltaE/nowT)>(LD)rand()/RAND_MAX);
		else swap(nowA[x],nowA[y]);
		nowT*=deltaT;
	}
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m);
	for(Re i=1;i<=n;++i)in(A[i]),S+=A[i];x0=(LD)S/m;
	for(Re i=1;i<=n;++i)ansA[i]=A[i];
	Srand(965579261),Random(ansA,n),Srand(20030825);
	ans=calc(ansA),fire(),fire(),fire(),fire(),fire();
	printf("%.2lf\n",sqrt(ans));
}
