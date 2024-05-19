#include<cstdio>
#define Re register int
using namespace std;
const int N=1003,P=998244353;
int C_[N][N]; 
inline int C(Re m,Re n){
    if(m>n)return 0;
    if(!m||m==n)return C_[m][n]=1;
    if(C_[m][n])return C_[m][n];
    return C_[m][n]=(C(m,n-1)+C(m-1,n-1))%P;
}
int main(){}
