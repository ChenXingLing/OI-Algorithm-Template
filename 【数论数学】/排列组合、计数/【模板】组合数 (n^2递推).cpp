#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1003,P=998244353;
int C[N][N];
inline void get_C(Re N){
	for(Re i=0;i<=N;++i)C[0][i]=C[i][i]=1;
	for(Re i=1;i<=N;++i)
		for(Re j=1;j<i;++j)
			C[j][i]=(C[j-1][i-1]+C[j][i-1])%P;
}
int main(){}
