#include<bits/stdc++.h>
#define LL long long
#define Re register LL
using namespace std;
const LL inf=1000,N=20;
LL vis[inf+5];char A[N+5],B[N+5];
inline LL fu(){return rand()%2?-1:1;}
inline LL Rand(LL L,LL R){
	LL a=R-L+1;
	LL b=(LL)rand()*rand()%a+1;
	b=b*rand()%a+1;
	b=b*rand()%a+1;
	b=b*rand()%a+1;
	b=b*rand()%a+1;
	return L+b-1;
}
LL lo[N],tp[N];
int main(){
//	freopen("data.in","w",stdout);
	srand(time(0));
	Re n=rand()%N+1;
	printf("%lld 0\n",n);
	for(Re i=1;i<=n;++i)printf("%lld ",Rand(1,inf));
}
