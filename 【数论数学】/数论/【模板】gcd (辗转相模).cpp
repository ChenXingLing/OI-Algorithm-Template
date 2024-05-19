#include<cstdio>
int n,a,b;
inline int GCD(int a,int b){while(b^=a^=b^=a%=b);return a;}
inline int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int main(){
	scanf("%d",&n);
	while(n--)scanf("%d%d",&a,&b),printf("%d\n",GCD(a,b));
}