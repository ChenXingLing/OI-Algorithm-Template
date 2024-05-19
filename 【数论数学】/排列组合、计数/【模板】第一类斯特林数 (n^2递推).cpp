#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1003,P=998244353;
int s[N][N]; 
inline void get_stiring(Re N){
	for(Re i=0;i<=N;++i)s[i][i]=1;
	for(Re i=1;i<=N;++i)
		for(Re j=1;j<i;++j)
			s[j][i]=s[j-1][i-1]+(LL)(i-1)*s[j][i-1]%P;
}
int main(){}
