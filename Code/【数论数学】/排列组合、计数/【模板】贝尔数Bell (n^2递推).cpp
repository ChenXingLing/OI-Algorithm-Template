#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1003,P=998244353;
int B[N],C[N][N],S[N][N];
inline void get_C(Re N){
	for(Re i=0;i<=N;++i)C[0][i]=C[i][i]=1;
	for(Re i=1;i<=N;++i)
		for(Re j=1;j<i;++j)
			C[j][i]=(C[j-1][i-1]+C[j][i-1])%P;
}
inline void get_Bell(Re N){
	B[0]=1,get_C(N);
	for(Re i=1;i<=N;++i)
		for(Re j=0;j<=i-1;++j)
			(B[i]+=(LL)C[j][i-1]*B[j]%P)%=P;
}
inline void get_Stiring(Re N){
	for(Re i=0;i<=N;++i)S[i][i]=1;
	for(Re i=1;i<=N;++i)
		for(Re j=1;j<i;++j)
			S[j][i]=S[j-1][i-1]+(LL)j*S[j][i-1]%P;
}
inline void get_Bell_(Re N){
	B[0]=1,get_Stiring(N);
	for(Re i=1;i<=N;++i)
		for(Re j=1;j<=i;++j)
			(B[i]+=S[j][i])%=P;
}
int main(){}
