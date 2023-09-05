#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1003,P=998244353;
int S[N][N]; 
inline void get_Stiring(Re N){
	for(Re i=0;i<=N;++i)S[i][i]=1;
	for(Re i=1;i<=N;++i)
		for(Re j=1;j<i;++j)
			S[j][i]=S[j-1][i-1]+(LL)j*S[j][i-1]%P;
}
int main(){}
