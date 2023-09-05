#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1003,M=262144;
int n,K,V,A[N],cnt[M],f[M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(K),V=(1<<n)-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	memset(f,127,sizeof(f));
	f[0]=0;
	for(Re j=0;j<=V;++j)
		for(Re i=1;i<=n;++i)
			if(j&(1<<i-1))cnt[j]+=A[i];
	for(Re j=1;j<=V;++j)
		for(Re k=j;k;k=(k-1)&j)//枚举j的子集
			if(cnt[k]<=K)//新的一组选了k状态 
				f[j]=min(f[j],f[j-k]+1);
	printf("%d\n",f[V]);
}
